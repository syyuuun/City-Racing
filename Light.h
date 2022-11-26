#pragma once

#include "pch.h"
#include "Shader.h"

class Light {
private:
	static Light* pInst;
	glm::vec3 positionVector{ 0.0f, 3.0f, 0.0f };
	glm::vec3 lightColorVector{ 1.0f, 1.0f, 1.0f };
private:
	Light();
public:
	static Light* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Light;

		return pInst;
	}

	glm::vec3& getPosition();

	glm::vec3& getLightColor();

	void update() const;

	friend class Shader;
};