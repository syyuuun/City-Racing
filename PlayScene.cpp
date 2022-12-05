#include "PlayScene.h"

void PlayScene::initialize()
{
	std::cout << "Enter Play Scene" << "\n";	

	StageManager::getInstance()->initialize();

	CarManager::getInstance()->initialize();
	
	SceneManager::getInstance()->setCurrentSceneType(SceneManager::SceneType::PLAY);
	
	BackGround::getInstance()->setBGType(BackGround::BGType::PLAY);
}

void PlayScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::END);
		break;
	case 'w':
		Camera::getInstance()->getPositionVector().y += 0.1f;
		break;
	default:
		break;
	}
}

void PlayScene::inputSpecialKeyboard(int key, int x, int y)
{

}

void PlayScene::inputMouse(int button, int state, int x, int y)
{

}

void PlayScene::update()
{
	// Road Update

	
	// Obstacle update

	// Car update
	CarManager::getInstance()->update();
	Camera::getInstance()->update();

	// Light update
	Light::getInstance()->update();
}

void PlayScene::render()
{
	// BackGround render
	BackGround::getInstance()->render();

	// Map render
	StageManager::getInstance()->render();

	// Obstacle render

	// Car render
	CarManager::getInstance()->render();
}

void PlayScene::release()
{

}
