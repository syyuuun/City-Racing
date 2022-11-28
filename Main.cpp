#include "pch.h"
#include "GameFrameWork.h"

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid SpecialKeyboard(int, int, int);
GLvoid Update(int);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(Constant::winWidth / 4, Constant::winHeight / 4);
	glutInitWindowSize(Constant::winWidth, Constant::winHeight);
	glutCreateWindow(Constant::projectName);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cerr << "Unable to initialize GLEW" << "\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	GameFrameWork::getInstance()->initialize();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(10, Update, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	GameFrameWork::getInstance()->renderScene();
}

GLvoid Reshape(int w, int h)
{
	GameFrameWork::getInstance()->reshape(w,h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	GameFrameWork::getInstance()->inputKeyboard(key, x, y);
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	GameFrameWork::getInstance()->inputSpecialKeyboard(key, x, y);
	glutPostRedisplay();
}

GLvoid Update(int)
{
	GameFrameWork::getInstance()->update();
	glutPostRedisplay();
	glutTimerFunc(10, Update, 1);
}