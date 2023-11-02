#version 330 core

out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPosition;

in vec3 vNormal;
in vec3 fragPosition;

// 오브젝트의 meterial속성을 구조체로 묶음
struct Meterials {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

// uniform Meterials meterials;

void main(void)
{
	// calc lighting

	// clac ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// calc normal and light object direction
	vec3 vNorm = normalize(vNormal);
	vec3 lightDirection = normalize(lightPosition - fragPosition);

	// calc diffuse
	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = diffuseN * lightColor;

	// calc specular
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(viewPosition - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 resultColor  = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4 (resultColor, 1.0);
}