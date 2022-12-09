#include "PlayScene.h"

void PlayScene::initialize()
{
	std::cout << "Enter Play Scene" << "\n";	

	StageManager::getInstance()->initialize();

	CarManager::getInstance()->initialize();
	
	SceneManager::getInstance()->setCurrentSceneType(SceneManager::SceneType::PLAY);
	
	BackGround::getInstance()->setBGType(BackGround::BGType::PLAY);
	
	Camera::getInstance()->getPositionVector().y = 4.5f;

	std::cout << "Camera X: " << Camera::getInstance()->getPositionVector().x << "\n";
	std::cout << "Camera Y: " << Camera::getInstance()->getPositionVector().y << "\n";
	std::cout << "Camera Z: " <<  Camera::getInstance()->getPositionVector().z << "\n";
	std::cout << "Camera Look X: "<< Camera::getInstance()->getLookVector().x << "\n";
	std::cout << "Camera Look Y: " << Camera::getInstance()->getLookVector().y << "\n";
	std::cout << "Camera Look Z: " << Camera::getInstance()->getLookVector().x << "\n";
}

void PlayScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::END);
		break;
	case VK_SPACE:
		Sound::getInstance()->play(Sound::SoundType::JUMP);
		break;
		// 1ÀÎÄª ½ÃÁ¡
	case '1':
		Camera::getInstance()->setPerspective(Camera::Perspective::ONE);
		break;
		// 3ÀÎÄª ½ÃÁ¡ 
	case '3':
		Camera::getInstance()->setPerspective(Camera::Perspective::THIRD);
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
