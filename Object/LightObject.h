#pragma once
#include "Object/Object.h"

class LightObject : public Object {
public:
	LightObject();
	~LightObject();

private:

public:
	void Update(float deltaTime);
	void Render();

};