#pragma once
#include "pch.h"
#include "Sound.h"
#include "Manager.h"
#include "CarManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "BackGround.h"

class SceneManager : public Manager {
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

	virtual void initialize() override;

	void inputKeyboard(unsigned char key, int x, int y);

	void inputSpecialKeyboard(int key, int x, int y);

	void inputMouse(int button, int state, int x, int y);

	virtual void update() override;

	virtual void render() override;

	void setCurrentSceneType(SceneType);

	void changeScene(SceneType sceneType);

	SceneType getCurrentSceneType();
public:
	static SceneManager* getInstance();
};