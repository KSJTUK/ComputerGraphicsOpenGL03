#version 460 core
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 in_Texture; //--- �ؽ�ó ����: attribute position 1
layout (location = 2) in vec3 in_Normal; //--- ���� ��� ����: attribute position 2

uniform mat4 perspectiveMat;
uniform mat4 viewMat;
uniform mat4 modelsParentTransform;
uniform mat4 modelInitTransform;
uniform mat4 modelTransform;

// lighting
out vec3 vNormal;
out vec3 fragPosition;

void main(void)
{
	mat4 transform = modelsParentTransform * modelTransform * modelInitTransform;

	fragPosition = vec3(transform * vec4(in_Position, 1.0f));
	vNormal = mat3(transpose(inverse(transform))) * in_Normal;

	gl_Position = perspectiveMat * viewMat * vec4(fragPosition, 1.0f);

}