#pragma once
#include "CarManager.h"

class Porsche : public Car {
public:
	Porsche();

	virtual void initialize() override;

	virtual void readObj(const char* objName) override;

	virtual void inputKeyboard(unsigned char key, int x, int y) override;

	virtual void inputSpecialKeyboard(int key, int x, int y) override;

	virtual void inputMouse(int button, int state, int x, int y) override;

	virtual void update() override;

	virtual void render() override;

	virtual void release() override;

	virtual void collide() override;

	virtual GLint& getCollisionCount() override;

	friend class Shader;
};