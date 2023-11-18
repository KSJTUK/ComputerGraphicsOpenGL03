#version 330 core

const float epsilon = 0.000001f;

out vec4 FragColor;

in vec3 vNormal;
in vec3 fragPosition;

// 광원의 빛에 대한 계수들을 구조체로 묶음
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
	
	// 거리에 따른 감쇠값 Attenuation 계산을 위한 3가지 변수 설정
	// 분자 == 1.0, 분모 == constant + linear * distance + linear * distance * distance
	float constant;		// 상수항, 거의 모든 경우에서 1.0유지, 최종 결과의 분모 값을 1보다 작게 만들지 않기 위한 장치
	float linear;		// 거리값과 곱해지며 1차원 적인 방법으로 세기 감쇠, linear * distance
	float quadratic;	// 거리값과 곱해지며 2차원 적으로 세기 감쇠 quadratic * distance * distance
};

// 오브젝트의 meterial속성을 구조체로 묶음
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

vec3 calcLighting(Light light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	// calc lighting

	// 앰비언트 항
	// 앰비언트 빛의 RGB색상 과 물체의 앰비언트 계수간의 원소간 곱셈으로 정의
	// s * m (s == RGB, m == object's ambient)
	vec3 ambient = light.ambient * meterials.ambient;

	// 퐁모델의 디퓨즈 항
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

	// 퐁모델의 스페큘러 항
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = diffuseN <= epsilon ? 0.0f : pow(max(dot(viewDirection, reflectDirection), 0.0), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	return (ambient + diffuse + specular);
}

vec3 calcDirectionLighting(DirectionLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 ambient = light.ambient * meterials.ambient;

	// 퐁모델의 디퓨즈 항
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(-light.direction);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

	// 퐁모델의 스페큘러 항
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = diffuseN <= epsilon ? 0.0f : pow(max(dot(viewDirection, reflectDirection), 0.0), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	return (ambient + diffuse + specular);
}

vec3 calcPointLighting(PointLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 ambient = light.ambient * meterials.ambient;

	// 퐁모델의 디퓨즈 항
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

	// 퐁모델의 스페큘러 항
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = diffuseN <= epsilon ? 0.0f : pow(max(dot(viewDirection, reflectDirection), 0.0), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	float dist = length(light.position - fragPos);
	float attenuationUnder = light.constant + light.linear * dist + light.quadratic * dist * dist;
	float attenuation = 1.0 / attenuationUnder;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

void main(void)
{
//	 vec3 resultColor = calcLighting(light, vNormal, viewPosition, fragPosition);
	// vec3 resultColor = calcDirectionLighting(light, vNormal, viewPosition, fragPosition);
	vec3 resultColor = calcPointLighting(light, vNormal, viewPosition, fragPosition);
	FragColor = vec4 (resultColor, 1.0);
}