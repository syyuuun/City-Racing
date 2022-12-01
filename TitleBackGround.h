#pragma once
#include "pch.h"
#include "Object.h"
#include "Shader.h"
class TitleBackGround : public Object {
private:
	static TitleBackGround* pInst;
private:
	TitleBackGround();
public:
	static TitleBackGround* getInstance();

	virtual void initialize();

	virtual void readObj(const char* fileName);

	virtual void update();

	virtual void render();

	virtual void release();

	friend class Shader;
};