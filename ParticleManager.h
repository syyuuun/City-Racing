#pragma once

#include "pch.h"
#include "Manager.h"
#include "Particle.h"
#include "Shader.h"

class ParticleManager : public Manager {
private:
	static ParticleManager* pInst;
	std::list<Object*> particles;
	std::list<Object*>::iterator particleIter;
	size_t nParticle{ 20 };
	bool onParticleSystem{ false };
private:
	ParticleManager();
public:
	static ParticleManager* getInstance();

	virtual void initialize() override;

	virtual void update() override;
	 
	virtual void render() override;

	size_t getNParticle();


	bool& isOnParticleSystem();

	friend class Shader;
	friend class CarManager;
};