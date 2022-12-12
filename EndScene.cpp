#include "EndScene.h"

void EndScene::initialize()
{
	std::cout << "Enter Ending Scene" << "\n";
	SceneManager::getInstance()->setCurrentSceneType(SceneManager::SceneType::END);
	BackGround::getInstance()->setBGType(BackGround::BGType::END);
	Light::getInstance()->getPosition() = glm::vec3{ 0.0,0.0f,5.0f };
	Camera::getInstance()->getPositionVector() = glm::vec3{ 0.0f,0.0f,10.0f };
	Camera::getInstance()->getLookVector() = glm::vec3{ 0.0f,0.0f,0.0f };
}

void EndScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::TITLE);
		break;
	default:
		break;
	}
}

void EndScene::inputSpecialKeyboard(int key, int x, int y)
{
}

void EndScene::inputMouse(int button, int state, int x, int y)
{
}

void EndScene::update()
{
	Camera::getInstance()->update();
	Light::getInstance()->update();
}

void EndScene::render()
{
	BackGround::getInstance()->render();
}

void EndScene::release()
{
}

