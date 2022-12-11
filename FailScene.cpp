#include "FailScene.h"

void FailScene::initialize()
{
	std::cout << "Enter Fail Scene" << "\n";
	SceneManager::getInstance()->setCurrentSceneType(SceneManager::SceneType::FAIL);
	BackGround::getInstance()->setBGType(BackGround::BGType::FAIL);
	Camera::getInstance()->getPositionVector() = glm::vec3{ 0.0f,0.0f,10.0f };
	Camera::getInstance()->getLookVector() = glm::vec3{ 0.0f,0.0f,0.0f };
}

void FailScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_RETURN:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::PLAY);
		break;
	default:
		break;
	}
}

void FailScene::inputSpecialKeyboard(int key, int x, int y)
{
}

void FailScene::inputMouse(int button, int state, int x, int y)
{
}

void FailScene::update()
{
	Camera::getInstance()->update();
	Light::getInstance()->update();
}

void FailScene::render()
{
	BackGround::getInstance()->render();
}

void FailScene::release()
{
}