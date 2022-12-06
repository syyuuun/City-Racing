#pragma once
#include "pch.h"
#include "Shader.h"
#include "Light.h"
#include "Camera.h"
#include "Sound.h"
#include "SceneManager.h"
#include "CarManager.h"

class GameFrameWork {
private:
	static GameFrameWork* pInst;
public:
	GameFrameWork();
public:
	static GameFrameWork* getInstance();
	
	GLvoid initialize();

	GLvoid renderScene();

	GLvoid reshape(int w, int h);

	GLvoid inputKeyboard(unsigned char key, int x, int y);

	GLvoid inputSpecialKeyboard(int key, int x, int y);

	GLvoid inputMouse(int,int,int,int);
	
	GLvoid update();

	GLvoid release();
};