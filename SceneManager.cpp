#include "SceneManager.h"

SceneManager* SceneManager::pInst = nullptr;

SceneManager::SceneManager()
{
	currentScene = new TitleScene;
	currentScene->initialize();
}

SceneManager::~SceneManager()
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
	if (nullptr != currentScene) {
		delete currentScene;
		currentScene = nullptr;
	}

	switch (sceneType)
	{
	case SceneType::TITLE:
		currentScene = new TitleScene;
		break;
	case SceneType::SELECT:
		currentScene = new SelectScene;
		break;
	case SceneType::PLAY:
		currentScene = new PlayScene;
		break;
	case SceneType::END:
		currentScene = new EndScene;
		break;
	default:
		break;
	}

	currentScene->initialize();
}

SceneManager* SceneManager::getInstance()
{
	if (nullptr == pInst)
		pInst = new SceneManager;

	return pInst;
}