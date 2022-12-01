#include "TitleScene.h"

void TitleScene::initialize()
{
	std::cout << "Enter TitleScene" << "\n";
	BackGround::getInstance()->initialize();
	Light::getInstance()->getPosition() = glm::vec3{ 0.0f,5.0f,0.0f };
	Camera::getInstance()->getPositionVector() = glm::vec3{ 0.0f,0.0f,10.0f };
	BackGround::getInstance()->setBGType(BackGround::BGType::TITLE);
}

void TitleScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_SPACE:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::SELECT);
		break;
	default:
		break;
	}
}

void TitleScene::inputSpecialKeyboard(int key, int x, int y)
{

}

void TitleScene::inputMouse(int button, int state, int x, int y)
{

}

void TitleScene::update()
{
	Camera::getInstance()->update();
	Light::getInstance()->update();
}

void TitleScene::render()
{
	BackGround::getInstance()->render();
}

void TitleScene::release()
{
}