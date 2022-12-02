#pragma once
#include "pch.h"
#include "CarManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "BackGround.h"

class SceneManager {
protected:
	enum{ MaxNumOfScene = 4 };
public:
	enum class SceneType { TITLE = 0, SELECT, PLAY, END };
private:
	static SceneManager* pInst;
	static GLuint currentSceneIndex;
	Scene* currentScene{ nullptr };
	std::vector<Scene*> scenes;
	SceneType sceneType{ SceneType::TITLE };
private:
	SceneManager();
public:
	~SceneManager();

	void inputKeyboard(unsigned char key, int x, int y);

	void inputSpecialKeyboard(int key, int x, int y);

	void inputMouse(int button, int state, int x, int y);

	void update();

	void render();

	void setCurrentSceneType(SceneType);

	void changeScene(SceneType sceneType);

	SceneType getCurrentSceneType();
public:
	static SceneManager* getInstance();
};