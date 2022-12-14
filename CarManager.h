#pragma once

#include "pch.h"
#include "Shader.h"
#include "Manager.h"
#include "Car.h"
#include "Bmw.h"
#include "Porsche.h"
#include "Ford.h"

class CarManager : public Manager{
public:
	enum class CarType { BMW = 0, PORSCHE, FORD };
private:
	static CarManager* pInst;
	CarType curretCarType{ CarType::BMW };
	Car* currentCar{ nullptr };
	enum { MaxNumOfCar = 10 };// 최대 차량 개수
	size_t nCar; // 등록된 차량 개수
	std::vector<Car*> cars;
	GLint choiceIndex;
private:
	CarManager();
public:
	virtual void initialize() override;

	void select();

	void inputKeyboard(unsigned char key, int x, int y);

	void inputSpecialKeyboard(int key, int x, int y);

	void inputMouse(int button, int state, int x, int y);

	virtual void update() override;

	virtual void render() override;

	void changeCar(GLint);

	size_t getNCar();

	GLint& getChoiceIndex();

	Car*& getCurrentCar();

public:
	static CarManager* getInstance();
	friend class Shader;
};