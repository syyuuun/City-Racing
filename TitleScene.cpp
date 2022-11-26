#include "TitleScene.h"

void TitleScene::initialize()
{
	std::cout << "Enter TitleScene" << "\n";
}

void TitleScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_SPACE:
		SceneManager::getInstance()->changeScene(SceneType::SELECT);
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

}

void TitleScene::render()
{

}

void TitleScene::release()
{
}
