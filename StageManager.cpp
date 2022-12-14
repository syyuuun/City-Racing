#include "StageManager.h"

StageManager* StageManager::pInst = nullptr;

StageManager::StageManager()
{
	for (size_t i = 0; i < nRoads; ++i) {
		roads.emplace_back(new Road(glm::vec3{ 0.0f,-1.0f,0.0f + -20.0f * i }, glm::vec3{ 8.0f,0.1f,10.0f }));
	}
	for (size_t i = 0; i < nObstacles; ++i) {
		obstacles.emplace_back(new Obstacle(glm::vec3{randomXPos(mersenne),0.0f,0.0f + -5.0f + (-15.0f * i)}, glm::vec3{1.0,1.0f,1.0f}));
	}
}

void StageManager::initialize()
{
	for (size_t i = 0; i < nObstacles; ++i) {
			obstacles[i]->initialize();
	}
}

void StageManager::update()
{
	for (size_t i = 0; i < nRoads; ++i)
		roads[i]->update();

	for (size_t i = 0; i < nObstacles; ++i) {
		if (obstacles[i]->getCollision() == false)
			obstacles[i]->update();
	}
}

void StageManager::render()
{
	for (size_t i = 0; i < nRoads; ++i)
		roads[i]->render();

	for (size_t i = 0; i < nObstacles; ++i) {
		if (obstacles[i]->getCollision() == false)
			obstacles[i]->render();
	}
}

size_t StageManager::getNRoads()
{
	return nRoads;
}


size_t StageManager::getNObstacles()
{
	return nObstacles;
}

StageManager* StageManager::getInstance()
{
	if (nullptr == pInst)
		pInst = new StageManager;

	return pInst;
}

glm::vec3 StageManager::getPosition(int n)
{
	return obstacles[n]->getPositionVector();
}

void StageManager::setColideObstacle(int n)
{
	obstacles[n]->setCollision();
}

bool StageManager::getColideObstacle(int n)
{
	return obstacles[n]->getCollision();
}