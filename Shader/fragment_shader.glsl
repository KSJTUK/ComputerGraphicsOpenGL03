#version 330 core

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

// ������Ʈ�� meterial�Ӽ��� ����ü�� ����
struct Meterials {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform vec3 viewPosition;
uniform Meterials meterials;
uniform Light light;

void main(void)
{
	// calc lighting

	// �ں��Ʈ ��
	// �ں��Ʈ ���� RGB���� �� ��ü�� �ں��Ʈ ������� ���Ұ� �������� ����
	// s * m (s == RGB, m == object's ambient)
	vec3 ambient = light.ambient * meterials.ambient;

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(vNormal);
	vec3 lightDirection = normalize(light.position - fragPosition);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * meterials.diffuse);

	// ������ ����ŧ�� ��
	vec3 viewDirection = normalize(viewPosition - fragPosition);
	vec3 reflectDirection = reflect(lightDirection, vNorm);
	float spec = pow(max(dot(reflectDirection, viewDirection), 0.0), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	vec3 resultColor  = ambient + diffuse + specular;
	FragColor = vec4 (resultColor, 1.0);
}