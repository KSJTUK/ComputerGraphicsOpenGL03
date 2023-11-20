#version 460 core

const float lessThanZero = 0.000001f;

out vec4 FragColor;

in vec3 vNormal;
in vec3 fragPosition;

// ������ ���� ���� ������� ����ü�� ����
struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform vec3 viewPosition;
uniform Meterials meterials;
// uniform Light light;
// uniform DirectionLight light;
 uniform PointLight light;
//uniform FlashLight light;

vec3 calcLighting(Light light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	// calc lighting

	// �ں��Ʈ ��
	// �ں��Ʈ ���� RGB���� �� ��ü�� �ں��Ʈ ������� ���Ұ� �������� ����
	// s * m (s == RGB, m == object's ambient)
	vec3 ambient = light.ambient * meterials.ambient;

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

	// ������ ����ŧ�� ��
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	return (ambient + diffuse + specular);
}

vec3 calcDirectionLighting(DirectionLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 ambient = light.ambient * meterials.ambient;

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(-light.direction);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

	// ������ ����ŧ�� ��
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	return (ambient + diffuse + specular);
}

vec3 calcPointLighting(PointLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 ambient = light.ambient * meterials.ambient;

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

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
	vec3 ambient = light.ambient * meterials.ambient;

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

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
//	 vec3 resultColor = calcLighting(light, vNormal, viewPosition, fragPosition);
//	 vec3 resultColor = calcDirectionLighting(light, vNormal, viewPosition, fragPosition);
	vec3 resultColor = calcPointLighting(light, vNormal, viewPosition, fragPosition);
//	vec3 resultColor = calcFlashLighting(light, vNormal, viewPosition, fragPosition);

	FragColor = vec4 (resultColor, 1.0f);
}