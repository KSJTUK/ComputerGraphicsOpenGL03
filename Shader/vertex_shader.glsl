#version 330 core
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- 위치 변수: attribute position 0
layout (location = 1) in vec3 in_Texture; //--- 텍스처 변수: attribute position 1
layout (location = 2) in vec3 in_Normal; //--- 정점 노멀 변수: attribute position 2

uniform mat4 perspectiveMat;
uniform mat4 viewMat;
uniform mat4 modelsParentTransform;
uniform mat4 modelInitTransform;
uniform mat4 modelTransform;

// lighting
uniform vec3 lightObjectPosition;

out vec3 lightPosition;
out vec3 vNormal;
out vec3 fragPosition;

void main(void)
{
	mat4 transform = modelsParentTransform * modelTransform * modelInitTransform;

	vNormal = mat3(transpose(inverse(transform))) * in_Normal;
	fragPosition = vec3(transform * vec4(in_Position, 1.0f));
	lightPosition = vec3(viewMat * vec4(lightObjectPosition, 1.0f)) * in_Normal;

	gl_Position = perspectiveMat * viewMat * vec4(fragPosition, 1.0f);

}