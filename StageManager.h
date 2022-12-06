#pragma once

#include "pch.h"
#include "Shader.h"
#include "Stage.h"
#include "Road.h"
#include "SceneManager.h"

class StageManager {
private:
	static StageManager* pInst;
	std::vector<Stage*> roads;
	std::vector<Stage*> obstacles;
	size_t nRoads{ 100 };
	size_t nObstacles{ 20 };
private:
	StageManager();
public:
	void initialize();

	void update();

	void render();

	size_t getNRoads();

	size_t getNObstacles();
public:
	static StageManager* getInstance();

	friend class Shader;
};