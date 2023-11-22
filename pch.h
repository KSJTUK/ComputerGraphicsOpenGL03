#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtx/euler_angles.hpp>
#include <gl/glm/gtx/vector_angle.hpp>
#include <gl/glm/gtc/quaternion.hpp>	

#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <utility>
#include <list>

#include "Util/stb_image.h"

struct Vertex {
	glm::vec3 position{ };
	glm::vec2 texture{ };
	glm::vec3 normal{ };
};

// 생성할 윈도우의ㅡ 정보를 담을 구조체 정의
struct WindowInfo {
	int x;
	int y;
	int width;
	int height;
	float fWidth;
	float fHeight;
	char* windowTitle;
};

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

extern std::unique_ptr<class Engine> engine;

namespace constants {
	extern float gravity;
	extern float epsilon;
};

#define SHADER Shader::GetInstance()
#define LIGHTOBJECTSHADER LightObjectShader::GetInstance()
#define PARTICLESHADER ParticleShader::GetInstance()
#define MODELLIST ModelList::GetInstance()