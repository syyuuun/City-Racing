#include "CarManager.h"

CarManager* CarManager::pInst = nullptr;

CarManager::CarManager()
{
	cars.emplace_back(new Bmw);
	cars.emplace_back(new Porsche);
	cars.emplace_back(new Ford);
	
	// 수정 필요
	nCar = 3;

	for (size_t i = 0; i < nCar; ++i) {
		cars[i]->initialize();
	}

	choiceIndex = 0;
	currentCar = cars[choiceIndex];
}

void CarManager::initialize()
{
	currentCar->initialize();
}

void CarManager::select()
{

}

void CarManager::inputKeyboard(unsigned char key, int x, int y)
{
	currentCar->inputKeyboard(key, x, y);
}

void CarManager::inputSpecialKeyboard(int key, int x, int y)
{
	currentCar->inputSpecialKeyboard(key, x, y);
}

void CarManager::inputMouse(int button, int state, int x, int y)
{
	currentCar->inputMouse(button, state, x, y);
}

void CarManager::update()
{
	//if (sharedRotationDegree < 360.0f) {
	//	sharedRotationDegree += 1.0f;
	//}
	//else
	//	sharedRotationDegree = 0.0f;
	currentCar->update();
}

void CarManager::render()
{
	currentCar->render();
}

void CarManager::changeCar(GLint index)
{
	currentCar = cars[index];
	currentCar->initialize();
}

size_t CarManager::getNCar() { return nCar; }

CarManager* CarManager::getInstance()
{
	if (nullptr == pInst)
		pInst = new CarManager;

	return pInst;
}

GLint& CarManager::getChoiceIndex()
{ 
	return choiceIndex; 
}
