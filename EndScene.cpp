#include "EndScene.h"

void EndScene::initialize()
{
	std::cout << "Enter Ending Scene" << "\n";
}

void EndScene::inputKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		SceneManager::getInstance()->changeScene(SceneType::TITLE);
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

}

void EndScene::render()
{
}

void EndScene::release()
{
}
