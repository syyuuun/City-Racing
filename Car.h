#include "pch.h"
#include "Shader.h"
#include "Object.h"
#include "CarManager.h"
#include "SceneManager.h"

class Car : public Object {
protected:
	bool onInit{ false };
	glm::vec3 positionVector;
	glm::vec3 scaleVector;
	GLfloat rotationDegree{ 0.0f };
	float speed{ 0.0f };

public:
	virtual void inputKeyboard(unsigned char, int, int) = 0;

	virtual void inputSpecialKeyboard(int, int, int) = 0;

	virtual void inputMouse(int, int, int, int) = 0;

	friend class Shader;
};