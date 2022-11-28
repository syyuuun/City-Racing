#include "CarManager.h"

CarManager* CarManager::pInst = nullptr;

CarManager::CarManager()
{
	cars.emplace_back(new Bmw);
	cars.emplace_back(new Porsche);
	
	// 수정 필요
	nCar = 2;

	for (size_t i = 0; i < nCar; ++i) {
		cars[i]->initialize();
	}

	currentCar = cars[0];
}

void CarManager::initialize()
{
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
	currentCar->update();
}

void CarManager::render()
{
	currentCar->render();
}

void CarManager::changeCar(CarType carType)
{
	currentCar = cars[GLuint(carType)];
	currentCar->initialize();
}

size_t CarManager::getNCar() { return nCar; }

CarManager* CarManager::getInstance()
{
	if (nullptr == pInst)
		pInst = new CarManager;

	return pInst;
}
