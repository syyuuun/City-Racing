#include "Light.h"

Light* Light::pInst = nullptr;

Light::Light()
{

}

Light* Light::getInstance()
{
	if (nullptr == pInst)
		pInst = new Light;

	return pInst;
}

void Light::initialize()
{
	positionVector = glm::vec3{ 0.0f,1.0f,0.0f };
}

glm::vec3& Light::getPosition() { return positionVector; }

glm::vec3& Light::getLightColor() { return lightColorVector; }

void Light::update() const
{
	GLuint lightPosLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "lightPos"); // lightPos 전달 
	glUniform3f(lightPosLocation, Light::getInstance()->getPosition().x, Light::getInstance()->getPosition().y, Light::getInstance()->getPosition().z);
	GLuint lightColorLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "lightColor"); // lightColor 전달 
	glUniform3f(lightColorLocation, Light::getInstance()->getLightColor().x, Light::getInstance()->getLightColor().y, Light::getInstance()->getLightColor().z);
	GLuint viewPosLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewPos"); // viewPos 값 전달: 카메라 위치 
	glUniform3f(viewPosLocation, Camera::getInstance()->getPositionVector().x, Camera::getInstance()->getPositionVector().y, Camera::getInstance()->getPositionVector().z);
}

void Light::release()
{
	if (nullptr != pInst) {
		delete pInst;
		pInst = nullptr;
	}
}
