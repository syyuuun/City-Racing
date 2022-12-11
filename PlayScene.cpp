#include "PlayScene.h"

void PlayScene::initialize()
{
	std::cout << "Enter Play Scene" << "\n";	

	// 차량 위치 초기화

	// 카메라 초기화 

	// 장애물 초기화 

	// 맵 초기화 

	// 라이트 초기화 

	ParticleManager::getInstance()->initialize();

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
	case VK_SPACE:
		Sound::getInstance()->play(Sound::SoundType::JUMP);
		break;
		// 1인칭 시점
	case '1':
		Camera::getInstance()->setPerspective(Camera::Perspective::ONE);
		break;
		// 3인칭 시점 
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
	
	// Map update
	StageManager::getInstance()->update();

	// Camera update
	Camera::getInstance()->update();

	// Light update
	Light::getInstance()->update();

	ParticleManager::getInstance()->update();
}

void PlayScene::render()
{
	// Map render
	ParticleManager::getInstance()->render();

	StageManager::getInstance()->render();
	// Car render

	CarManager::getInstance()->render();

	ParticleManager::getInstance()->render();
}

void PlayScene::release()
{

}
