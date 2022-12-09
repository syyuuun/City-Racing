#pragma once

#include "pch.h"
#include "Shader.h"
#include "Object.h"
#include "StageManager.h"

class Stage : public Object {
	bool onCollision{ false };
public:
	friend class Shader;
	const glm::vec3& getPositionVector() const { return positionVector; }

	void setCollision() {
		onCollision = true;
	}
	bool getCollision() { return onCollision; }
};