#pragma once
#include "SceneManager.h"
#include "pch.h"

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;

	virtual void initialize() = 0;

	virtual void inputKeyboard(unsigned char key, int x, int y) = 0;
	
	virtual void inputSpecialKeyboard(int key, int x, int y) = 0;

	virtual void inputMouse(int button, int state, int x, int y) = 0;

	virtual void update() = 0;

	virtual void render() = 0;

	virtual void release() = 0;


};