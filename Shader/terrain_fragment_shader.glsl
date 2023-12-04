#version 460 core

in float height;
in vec2 tes_out_tex;
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

uniform Meterials meterial;

void main(void)
{
	meterial.specular;
	meterial.shininess;
	vec3 texColor = vec3(texture(meterial.heightMapTexture, tes_out_tex));

	fragColor = vec4(texColor, 1.0f);
}