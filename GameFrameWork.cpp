#include "GameFrameWork.h"

GameFrameWork* GameFrameWork::pInst = nullptr;

GameFrameWork::GameFrameWork()
{

}

GameFrameWork* GameFrameWork::getInstance()
{
	if (nullptr == pInst)
		pInst = new GameFrameWork;

	return pInst;
}

GLvoid GameFrameWork::initialize()
{
	CarManager::getInstance()->initialize();
	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
	Shader::getInstance()->initShader();
}

GLvoid GameFrameWork::renderScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	Shader::getInstance()->initBuffer();
	SceneManager::getInstance()->render();

	glutSwapBuffers();
}

GLvoid GameFrameWork::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid GameFrameWork::inputKeyboard(unsigned char key, int x, int y)
{
	SceneManager::getInstance()->inputKeyboard(key, x, y);
	glutPostRedisplay();
}

GLvoid GameFrameWork::inputSpecialKeyboard(int key, int x, int y)
{
	SceneManager::getInstance()->inputSpecialKeyboard(key, x, y);
	glutPostRedisplay();
}

GLvoid GameFrameWork::inputMouse(int button, int state, int x, int y)
{
	SceneManager::getInstance()->inputMouse(button, state, x, y);
	glutPostRedisplay();
}

GLvoid GameFrameWork::update()
{
	SceneManager::getInstance()->update();
}

GLvoid GameFrameWork::release()
{
	if (nullptr == pInst) {
		delete pInst;
		pInst = nullptr;
	}
}