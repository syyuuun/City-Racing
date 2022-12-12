#pragma once

#include "pch.h"
#include "Shader.h"

class Light {
private:
	static Light* pInst;
	glm::vec3 positionVector{ 0.0f, 1.0f, 0.0f };
	glm::vec3 lightColorVector{ 1.0f, 1.0f, 1.0f };
private:
	Light();
public:
	static Light* getInstance();

	void initialize();

	glm::vec3& getPosition();

	glm::vec3& getLightColor();

	void update() const;

	void release();

	friend class Shader;
};