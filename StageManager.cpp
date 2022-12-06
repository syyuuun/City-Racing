#include "StageManager.h"

StageManager* StageManager::pInst = nullptr;

StageManager::StageManager()
{
	for (size_t i = 0; i < nRoads; ++i) {
		roads.emplace_back(new Road(glm::vec3{ 0.0f,-0.5f,0.0f + -20.0f * i }, glm::vec3{ 8.0f,0.1f,10.0f }));
	}
}

void StageManager::initialize()
{

}

void StageManager::update()
{
	for (size_t i = 0; i < nRoads; ++i)
		roads[i]->update();
}

void StageManager::render()
{
	for (size_t i = 0; i < nRoads; ++i)
		roads[i]->render();
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
