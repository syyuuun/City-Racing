#include "PlayScene.h"

void PlayScene::initialize()
{
	std::cout << "Enter Play Scene" << "\n";	

	// Road Load
	 
	// Obstacle Road

	// Car Load
	
	// Camera Load
	 
	// Light Load
}

void PlayScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::END);
		break;
	default:
		break;
	}
}

void PlayScene::inputSpecialKeyboard(int key, int x, int y)
{
	CarManager::getInstance()->inputSpecialKeyboard(key, x, y);
}

void PlayScene::inputMouse(int button, int state, int x, int y)
{

}

void PlayScene::update()
{
	// Road Update

	// Obstacle update

	// Car update
	Camera::getInstance()->update();

	// Light update
	Light::getInstance()->update();
}

void PlayScene::render()
{
	// Road render

	// Obstacle render

	// Car render
	CarManager::getInstance()->render();
}

void PlayScene::release()
{

}
