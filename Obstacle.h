#pragma once
#include "StageManager.h"

class Obstacle : public Stage {
private:
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_int_distribution<GLint> uiDir{ -1,1 };
	//bool onCollision{ false };
	int direction{ uiDir(mersenne) };
	float speed{ 0.0f };
public:
	Obstacle(const glm::vec3& pos, const glm::vec3& scale);

	virtual void initialize();

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();

};