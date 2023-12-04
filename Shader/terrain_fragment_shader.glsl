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
	
	// 거리에 따른 감쇠값 Attenuation 계산을 위한 3가지 변수 설정
	// 분자 == 1.0, 분모 == constant + linear * distance + linear * distance * distance
	float constant;		// 상수항, 거의 모든 경우에서 1.0유지, 최종 결과의 분모 값을 1보다 작게 만들지 않기 위한 장치
	float linear;		// 거리값과 곱해지며 1차원 적인 방법으로 세기 감쇠, linear * distance
	float quadratic;	// 거리값과 곱해지며 2차원 적으로 세기 감쇠 quadratic * distance * distance
};

// Spot Light 카메라를 기준으로 비추는 조명
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

// 오브젝트의 meterial속성을 구조체로 묶음
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