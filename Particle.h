#pragma once

#include "pch.h"
#include "Object.h"
#include "Shader.h"

class Particle : public Object {
private:
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