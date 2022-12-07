#include "PlayScene.h"

void PlayScene::initialize()
{
	std::cout << "Enter Play Scene" << "\n";	

	StageManager::getInstance()->initialize();

	CarManager::getInstance()->initialize();
	
	SceneManager::getInstance()->setCurrentSceneType(SceneManager::SceneType::PLAY);
	
	BackGround::getInstance()->setBGType(BackGround::BGType::PLAY);
	
	Camera::getInstance()->getPositionVector().y = 4.5f;
}

void PlayScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::END);
		break;
		// 1ÀÎÄª ½ÃÁ¡
	case '1':
		break;
		// 3ÀÎÄª ½ÃÁ¡ 
	case '3':
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
	// Car update
	CarManager::getInstance()->update();
	
	// Camera update
	Camera::getInstance()->update();

	// Light update
	Light::getInstance()->update();
}

void PlayScene::render()
{
	// Map render
	StageManager::getInstance()->render();

	// Car render
	CarManager::getInstance()->render();
}

void PlayScene::release()
{

}
