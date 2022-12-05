#pragma once
#include "pch.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "CarManager.h"
#include "StageManager.h"
#include "BackGround.h"

class Shader {
private:
	static Shader* pInst;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;
private:
	Shader();
public:
	static Shader* getInstance();

	const GLuint& getShaderProgram() const;

	char* file2Buffer(const char* file);

	void makeVertexShader();

	void makeFragmentShader();

	void checkCompileError(const GLuint& shaderType, const char* name);

	void glGenerate();

	void initShader();

	void initTexture();

	void initBuffer();

	void release();

	friend class Camera;
	friend class Light;
	friend class CarManager;
	friend class StageManager;
	friend class BackGround;
};
