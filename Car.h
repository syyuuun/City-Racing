#include "pch.h"
#include "Shader.h"
#include "Object.h"
#include "CarManager.h"
#include "SceneManager.h"

class Car : public Object {
protected:
	bool onInit{ false };
	bool onJump{ false };
	glm::vec3 positionVector;
	glm::vec3 scaleVector;
	GLfloat rotationDegree{ 0.0f };
	GLfloat speed{ 0.0f };
	GLfloat mass{ 0.2f };
	GLfloat jumpVelocity{ 2.0f };
	GLfloat jumpForce{ 0.0f };
public:
	virtual void inputKeyboard(unsigned char, int, int) = 0;

	virtual void inputSpecialKeyboard(int, int, int) = 0;

	virtual void inputMouse(int, int, int, int) = 0;

	const glm::vec3& getPositionVector() const { return positionVector; }

	bool& isOnJump() { return onJump; }

	const GLfloat& getJumpVelocity() const { return jumpVelocity; }

	const GLfloat& getJumpForce() const { return jumpForce; }

	void collide()
	{ 
		Sound::getInstance()->play(Sound::SoundType::COLLISION);
		speed = 0.0f; 
	}

	friend class Shader;
};