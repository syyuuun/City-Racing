#include "SelectScene.h"

void SelectScene::initialize()
{
	std::cout << "Enter Select Scene" << "\n";
	CarManager::getInstance()->initialize();
	BackGround::getInstance()->setBGType(BackGround::BGType::SELECT);
}

void SelectScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::TITLE);
		break;
	case VK_RETURN:
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::PLAY);
		break;
	default:
		break;
	}
}

void SelectScene::inputSpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		std::cout << "LEFT" << "\n";
		CarManager::getInstance()->changeCar(CarManager::CarType::BMW);
		break;
	case GLUT_KEY_RIGHT:
		std::cout << "Right" << "\n";
		CarManager::getInstance()->changeCar(CarManager::CarType::PORSCHE);
		break;
	default:
		break;
	}
}

void SelectScene::inputMouse(int button, int state, int x, int y)
{
}

void SelectScene::update()
{
	CarManager::getInstance()->update();
	Camera::getInstance()->update();
	Light::getInstance()->update();
}

void SelectScene::render()
{
	BackGround::getInstance()->render();
	CarManager::getInstance()->render();
}

void SelectScene::release()
{

}
