#include "ParticleManager.h"

ParticleManager* ParticleManager::pInst = nullptr;

ParticleManager::ParticleManager()
{
	for (size_t i = 0; i < nParticle; ++i) {
		particles.emplace_back(new Particle);
	}
}

ParticleManager* ParticleManager::getInstance()
{
	if (nullptr == pInst)
		pInst = new ParticleManager;

	return pInst;
}

void ParticleManager::initialize()
{
	for (auto& element : particles)
		element->initialize();
}

void ParticleManager::update()
{
	if (onParticleSystem) {
		for (auto& element : particles)
			element->update();
	}
}

void ParticleManager::render()
{
	if (onParticleSystem) {
		for (const auto& element : particles)
			element->render();
	}
}

size_t ParticleManager::getNParticle() { return nParticle; }

bool& ParticleManager::isOnParticleSystem() { return onParticleSystem; }