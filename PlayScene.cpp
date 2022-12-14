#include "PlayScene.h"

void PlayScene::initialize()
{
	std::cout << "Enter Play Scene" << "\n";	

	// ��ֹ� �ʱ�ȭ �� �ʱ�ȭ 
	StageManager::getInstance()->initialize();
	BackGround::getInstance()->setBGType(BackGround::BGType::PLAY);
	SceneManager::getInstance()->setCurrentSceneType(SceneManager::SceneType::PLAY);

	// ���� �ʱ�ȭ
	CarManager::getInstance()->initialize();

	// ī�޶� �ʱ�ȭ 
	Camera::getInstance()->getPositionVector().z = 10.0f;
	Camera::getInstance()->getPositionVector().y = 5.0f;

	// ����Ʈ �ʱ�ȭ 
	Light::getInstance()->initialize();

	// ��ƼŬ �ʱ�ȭ
	ParticleManager::getInstance()->initialize();

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
		// 1��Ī ����
	case '1':
		Camera::getInstance()->setPerspective(Camera::Perspective::ONE);
		break;
	case '2':
		Camera::getInstance()->setPerspective(Camera::Perspective::TWO);
		break;
		// 3��Ī ���� 
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
