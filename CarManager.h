#pragma once

#include "pch.h"
#include "Shader.h"
#include "Car.h"
#include "Bmw.h"
#include "Porsche.h"

class CarManager {
public:
	enum class CarType{BMW =0, PORSCHE};
private:
	static CarManager* pInst;
	CarType curretCarType{ CarType::BMW };
	Car* currentCar{ nullptr };
	enum { MaxNumOfCar = 10 };// 최대 차량 개수
	size_t nCar; // 등록된 차량 개수
	std::vector<Car*> cars;
private:
	CarManager();
public:
	void initialize();

	void select();

	void inputKeyboard(unsigned char key, int x, int y);

	void inputSpecialKeyboard(int key, int x, int y);

	void inputMouse(int button, int state, int x, int y);

	void update();

	void render();

	void changeCar(CarType carType);

	size_t getNCar();

	void release();

public:
	static CarManager* getInstance();
	friend class Shader;
};
