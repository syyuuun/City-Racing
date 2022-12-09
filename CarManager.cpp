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
	currentCar->update();
	int n = StageManager::getInstance()->getNObstacles();
	glm::vec3 v = currentCar->getPositionVector();
	for (int i = 0; i < n; ++i) {
		glm::vec3 t = StageManager::getInstance()->getPosition(i);
		if (
			StageManager::getInstance()->getColideObstacle(i) == false
			&& v.x + 1 > t.x - 1
			&& v.x - 1 < t.x + 1
			&& v.z + 1 > t.z - 1.3
			&& v.z - 1 < t.z + 1.3
			&& v.y - t.y < 1.0) {
			std::cout << "col" << std::endl;
			currentCar->collide();
			StageManager::getInstance()->setColideObstacle(i);
			break;
		}
	}
	std::cout << "Car position X: " << currentCar->getPositionVector().x << "\n";
	std::cout << "Car position Y: " << currentCar->getPositionVector().y << "\n";
	std::cout << "Car position Z: " << currentCar->getPositionVector().z << "\n";
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

Car*& CarManager::getCurrentCar() { return currentCar; }

GLint& CarManager::getChoiceIndex()
{ 
	return choiceIndex; 
}
