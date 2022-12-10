#include "SceneManager.h"

SceneManager* SceneManager::pInst = nullptr;

SceneManager::SceneManager()
{
	scenes.emplace_back(new TitleScene);
	scenes.emplace_back(new SelectScene);
	scenes.emplace_back(new PlayScene);
	scenes.emplace_back(new EndScene);
	
	currentScene = scenes[GLuint(SceneManager::SceneType::TITLE)];
	
	currentScene->initialize();
}

SceneManager::~SceneManager()
{

}

void SceneManager::initialize()
{
}

void SceneManager::inputKeyboard(unsigned char key, int x, int y)
{
	currentScene->inputKeyboard(key, x, y);
}

void SceneManager::inputSpecialKeyboard(int key, int x, int y)
{
	currentScene->inputSpecialKeyboard(key, x, y);
}

void SceneManager::inputMouse(int button, int state, int x, int y)
{
	currentScene->inputMouse(button, state, x, y);
}

void SceneManager::update()
{
	currentScene->update();
}

void SceneManager::render()
{
	currentScene->render();
}

void SceneManager::changeScene(SceneType sceneType)
{
	currentScene = scenes[GLuint(sceneType)];
	currentScene->initialize();
}

SceneManager::SceneType SceneManager::getCurrentSceneType() { return sceneType; }

void SceneManager::setCurrentSceneType(SceneType type) { sceneType = type; }

SceneManager* SceneManager::getInstance()
{
	if (nullptr == pInst)
		pInst = new SceneManager;

	return pInst;
}