#pragma once
#include "SceneManager.h"
#include "CarManager.h"

class SelectScene : public Scene {
	virtual void initialize() override;

	virtual void inputKeyboard(unsigned char, int, int) override;

	virtual void inputSpecialKeyboard(int, int, int) override;

	virtual void inputMouse(int, int, int, int) override;

	virtual void update() override;

	virtual void render() override;

	virtual void release() override;
};