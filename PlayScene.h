#pragma once
#include "CarManager.h"
#include "StageManager.h"
#include "SceneManager.h"

class PlayScene : public Scene {
public:
	virtual void initialize() override;

	virtual void inputKeyboard(unsigned char, int, int) override;

	virtual void inputSpecialKeyboard(int, int, int) override;

	virtual void inputMouse(int, int, int, int) override;

	virtual void update() override;

	virtual void render() override;

	virtual void release() override;
};