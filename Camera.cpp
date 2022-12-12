#include "Camera.h"

Camera* Camera::pInst = nullptr;

Camera::Camera()
{

}

Camera* Camera::getInstance()
{
	if (nullptr == pInst)
		pInst = new Camera;

	return pInst;
}

glm::vec3& Camera::getPositionVector()
{
	return positionVector;
}

glm::vec3& Camera::getLookVector()
{
	return lookVector;
}

glm::vec3& Camera::getDirectionVector()
{
	return directionVector;
}

glm::vec3& Camera::getUpVector()
{
	return upVector;
}

glm::vec3& Camera::getRightVector()
{
	return rightVector;
}

glm::vec3& Camera::getDefaultUpVector()
{
	return defaultUpVector;
}

void Camera::setPerspective(Perspective p)
{
	perspective = p;
}

void Camera::update()
{
	if (SceneManager::SceneType::PLAY == SceneManager::getInstance()->getCurrentSceneType()) {
		switch (perspective)
		{
		case Camera::Perspective::ONE:
			positionVector.x = CarManager::getInstance()->getCurrentCar()->getPositionVector().x;
			positionVector.y = CarManager::getInstance()->getCurrentCar()->getPositionVector().y + 0.7f;
			positionVector.z = CarManager::getInstance()->getCurrentCar()->getPositionVector().z - 3.0f;
			lookVector.x = positionVector.x;
			lookVector.y = positionVector.y;
			lookVector.z = positionVector.z - 0.5f;
			break;
		case Camera::Perspective::TWO:
			positionVector.x = 0.0f;
			positionVector.y = 2.5f;
			positionVector.z = CarManager::getInstance()->getCurrentCar()->getPositionVector().z + 5.0f;
			lookVector.x = 0.0f;
			lookVector.y = 0.3f;
			lookVector.z = CarManager::getInstance()->getCurrentCar()->getPositionVector().z;
			break;
		case Camera::Perspective::THIRD:
			positionVector.x = 0.0f;
			positionVector.y = 4.5f;
			positionVector.z = CarManager::getInstance()->getCurrentCar()->getPositionVector().z + 10.0f;
			lookVector.x = 0.0f;
			lookVector.y = 0.0f;
			lookVector.z = CarManager::getInstance()->getCurrentCar()->getPositionVector().z;
			break;
		default:
			break;
		}
	}

	viewMatrix = glm::lookAt(positionVector, lookVector, upVector);
	projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
	unsigned int viewTrasnformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewTransform");
	unsigned int projectionTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "projectionTransform");
	glUniformMatrix4fv(viewTrasnformLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Camera::release()
{
	if (nullptr != pInst) {
		delete pInst;
		pInst = nullptr;
	}
}
