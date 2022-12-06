#pragma once
#include "StageManager.h"

class Obstacle : public Stage {
private:
	bool onCollision{ false };
public:
	Obstacle(const glm::vec3& pos, const glm::vec3& scale);

	virtual void initialize();

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();
};