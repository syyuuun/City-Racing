#pragma once

#include "pch.h"
#include "Shader.h"
#include "Object.h"
#include "StageManager.h"

class Stage : public Object {
public:
	friend class Shader;
	const glm::vec3& getPositionVector() const { return positionVector; }
};