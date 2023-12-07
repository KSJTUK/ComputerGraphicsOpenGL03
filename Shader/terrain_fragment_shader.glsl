#version 460 core

in float height;
in vec2 tes_out_tex;
in vec3 tes_out_normal;
in vec3 tes_out_fragPosition;

out vec4 fragColor;

struct DirectionLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	// �Ÿ��� ���� ���谪 Attenuation ����� ���� 3���� ���� ����
	// ���� == 1.0, �и� == constant + linear * distance + linear * distance * distance
	float constant;		// �����, ���� ��� ��쿡�� 1.0����, ���� ����� �и� ���� 1���� �۰� ������ �ʱ� ���� ��ġ
	float linear;		// �Ÿ����� �������� 1���� ���� ������� ���� ����, linear * distance
	float quadratic;	// �Ÿ����� �������� 2���� ������ ���� ���� quadratic * distance * distance
};

// Spot Light ī�޶� �������� ���ߴ� ����
struct FlashLight {
	vec3 position;
	vec3 direction;
	float cutOff; // cutOff -> value of result cos(theta) oper
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

// ������Ʈ�� meterial�Ӽ��� ����ü�� ����
struct Meterials {
	sampler2D heightMapTexture;
	vec3 specular;
	float shininess;
};

uniform Meterials meterials;

uniform vec3 viewPosition;

uniform DirectionLight dirLight;
uniform PointLight pointLight;
uniform FlashLight spotLight;

vec3 calcDirectionLighting(DirectionLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 textureDiffuse = vec3(texture(meterials.heightMapTexture, tes_out_tex));
	vec3 ambient = light.ambient * textureDiffuse;

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(-light.direction);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * textureDiffuse);

	// ������ ����ŧ�� ��
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	return (ambient + diffuse + specular);
}

vec3 calcPointLighting(PointLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 ambient = light.ambient * vec3(texture(meterials.heightMapTexture, tes_out_tex));

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * vec3(texture(meterials.heightMapTexture, tes_out_tex)));

	// ������ ����ŧ�� ��
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	float dist = length(light.position - fragPos);
	float attenuationUnder = light.constant + light.linear * dist + light.quadratic * dist * dist;
	float attenuation = 1.0f / attenuationUnder;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calcFlashLighting(FlashLight light, vec3 normal, vec3 viewPos,  vec3 fragPos)
{
	vec3 lightDirection = normalize(light.position - fragPos);
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	vec3 resultColor = vec3(0.0f);
	vec3 ambient = light.ambient * vec3(texture(meterials.heightMapTexture, tes_out_tex));

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * vec3(texture(meterials.heightMapTexture, tes_out_tex)));

	// ������ ����ŧ�� ��
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec =  pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	float dist = length(light.position - fragPos);
	float attenuationUnder = light.constant + light.linear * dist + light.quadratic * (dist * dist);
	float attenuation = 1.0f / attenuationUnder;

	// ambient *= attenuation; // remove ambient * attenuation
	diffuse *= intensity;
	specular *= intensity; 

	return ambient + diffuse + specular;
}

void main(void)
{
	vec3 resultColor = calcDirectionLighting(dirLight, tes_out_normal, viewPosition, tes_out_fragPosition);

	resultColor += calcPointLighting(pointLight, tes_out_normal, viewPosition, tes_out_fragPosition);

	resultColor += calcFlashLighting(spotLight, tes_out_normal, viewPosition, tes_out_fragPosition);

	fragColor = vec4(resultColor, 1.0f);
//	fragColor = vec4(tes_out_normal, 1.0f);
}