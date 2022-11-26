#include "CarManager.h"

CarManager* CarManager::pInst = nullptr;

CarManager::CarManager()
{
	if (nullptr == currentCar) {
		currentCar = new Bmw;
		curretCarType = CarType::BMW;
	}
	currentCar->initialize();
}

void CarManager::initialize()
{
	if (nullptr == currentCar) {
		currentCar = new Bmw;
		curretCarType = CarType::BMW;
	}
	currentCar->initialize();
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
	if (nullptr != currentCar) {
		delete currentCar;
		currentCar = nullptr;
	}

	switch (carType)
	{
	case CarManager::CarType::BMW:
		currentCar = new Bmw;
		break;
	case CarManager::CarType::PORSCHE:
		currentCar = new Porsche;
		break;
	default:
		break;
	}
	curretCarType = carType;
	currentCar->initialize();
	Shader::getInstance()->glGenerate();
}

CarManager* CarManager::getInstance()
{
	if (nullptr == pInst)
		pInst = new CarManager;

	return pInst;
}
