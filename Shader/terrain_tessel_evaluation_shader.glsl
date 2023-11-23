#version 460 core

layout (triangles, fractional_odd_spacing, ccw) in;

in vec2 tcs_out_tex[];
in vec3 tcs_out_normal[];

out float Height;

uniform sampler2D heightMap;

void main()
{
    // 배지어 패치의 가중치 받아오기
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float w = gl_TessCoord.z;

	// 배지어 패치의 컨트롤 포인트 설정
	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;

	// 컨트롤 포인트에 가중치를 곱하고 더한 보간을 통해 새로운 정점 생성
	vec4 p = u * p0 + v * p1 + w * p2;
    vec2 texCoord = u * tcs_out_tex[0] + v * tcs_out_tex[1] + w * tcs_out_tex[2];


    Height = texture(heightMap, texCoord).y * 128.0f - 64.0f;

    vec3 normal = u * tcs_out_normal[0] + v * tcs_out_normal[1] + w * tcs_out_normal[2];

	// 노멀에 구해진 높이를 곱해서 정점을 높이만큼 옮김
    p += vec4(normal * Height, 0.f);

    gl_Position = p;
}
