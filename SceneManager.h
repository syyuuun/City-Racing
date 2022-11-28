#pragma once
#include "pch.h"
#include "CarManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "EndScene.h"

class SceneManager {
protected:
	enum{ MaxNumOfScene = 4 };
private:
	static SceneManager* pInst;
	static GLuint currentSceneIndex;
	Scene* currentScene{ nullptr };
	std::vector<Scene*> scenes;
public:
	enum class SceneType { TITLE = 0, SELECT, PLAY, END };
private:
	SceneManager();
public:
	~SceneManager();

	void inputKeyboard(unsigned char key, int x, int y);

	void inputSpecialKeyboard(int key, int x, int y);

	void inputMouse(int button, int state, int x, int y);

	void update();

	void render();

	void changeScene(SceneType sceneType);
public:
	static SceneManager* getInstance();
};