#include "Light.h"

Light* Light::pInst = nullptr;

Light::Light()
{

}

glm::vec3& Light::getPosition() { return positionVector; }

glm::vec3& Light::getLightColor() { return lightColorVector; }

void Light::update() const
{

}
