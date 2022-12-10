#pragma once

#include "pch.h"
#include "Object.h"
#include "Shader.h"

class Particle : public Object {
private:
	std::mt19937 mersenne;
	std::uniform_int_distribution<GLint> randomColor{ 0,3 };
	std::uniform_int_distribution<GLint> randomDir{ 0,7 };
	std::uniform_real_distribution<GLfloat> randomMoveAmount{ 0.1f,0.3f };
	GLuint myColor;
	GLint dir;
	GLfloat moveAmount;
public:
	Particle();

	virtual void initialize() override;

	virtual void readObj(const char*) override;

	virtual void update() override;

	virtual void render() override;

	virtual void release() override;

	void setPositionVector(const glm::vec3&);
};