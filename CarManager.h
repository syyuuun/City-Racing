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
private:
	CarManager();
public:
	void initialize();

	void inputKeyboard(unsigned char key, int x, int y);

	void inputSpecialKeyboard(int key, int x, int y);

	void inputMouse(int button, int state, int x, int y);

	void update();

	void render();

	void changeCar(CarType carType);
public:
	static CarManager* getInstance();
	friend class Shader;
};
