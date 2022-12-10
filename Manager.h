#pragma once

class Manager {
public:
	virtual void initialize() = 0;

	virtual void update() = 0;
	
	virtual void render() = 0;
};