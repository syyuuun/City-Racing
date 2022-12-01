#pragma once
#include "pch.h"
#include "Object.h"
#include "Shader.h"
class BackGround : public Object {
public:
	enum class BGType{TITLE, SELECT, PLAY, END};
private:
	static BackGround* pInst;
	GLuint textures[4];
	BGType bg{ BGType::TITLE};
private:
	BackGround();
public:
	static BackGround* getInstance();

	virtual void initialize();

	virtual void readObj(const char* fileName);

	virtual void update();

	virtual void render();

	virtual void release();

	void setBGType(BGType);

	friend class Shader;
};