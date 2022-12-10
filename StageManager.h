#pragma once

#include "pch.h"
#include "Shader.h"
#include "Manager.h"
#include "Stage.h"
#include "Road.h"
#include "Obstacle.h"
#include "SceneManager.h"

class StageManager : public Manager{
private:
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> randomXPos{ -5.0f,5.0f };
	static StageManager* pInst;
	std::vector<Object*> roads;
	std::vector<Stage*> obstacles;
	std::list<Stage*>::iterator obsIter;
	size_t nRoads{ 100 };
	size_t nObstacles{ 200 };
private:
	StageManager();
public:
	virtual void initialize() override;

	virtual void update() override;

	virtual void render() override;

	size_t getNRoads();

	size_t getNObstacles();

	glm::vec3 getPosition(int);

	void setColideObstacle(int);

	bool getColideObstacle(int);

public:
	static StageManager* getInstance();

	friend class Shader;
};