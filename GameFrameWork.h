#pragma once

class GameFrameWork {
public:
	static GameFrameWork* getInstance()
	{
		static GameFrameWork* pInst = nullptr;

		if (nullptr == pInst)
			pInst = new GameFrameWork;

		return pInst;
	}
public:
	GLvoid renderScene()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);










		glutSwapBuffers();
	}

	GLvoid reshape(int w, int h)
	{
		glViewport(0, 0, w, h);
	}

	GLvoid inputKeyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		default:
			break;
		}

		glutPostRedisplay();
	}

	GLvoid inputSpecialKeyboard(int key, int x, int y)
	{
		switch (key)
		{
		default:
			break;
		}
		glutPostRedisplay();
	}

	GLvoid inputMouse()
	{
		glutPostRedisplay();
	}
	
	GLvoid update()
	{

	}
};