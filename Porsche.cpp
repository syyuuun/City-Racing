﻿#include "Porsche.h"

Porsche::Porsche()
{
	readObj("Resources/Car/PORSCHE/Porsche_911_GT2.obj");
}

void Porsche::initialize()
{
	scaleVector = glm::vec3{ 1.0f,1.0f,2.0f };
	positionVector = glm::vec3{ 0.0f,0.0f,0.0f };
	rotationDegree = 0.0f;
}

void Porsche::readObj(const char* objName)
{
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempUvs;
	GLfloat sumX{ 0.0f }, sumY{ 0.0f }, sumZ{ 0.0f };
	GLfloat aveX{ 0.0f }, aveY{ 0.0f }, aveZ{ 0.0f };
	GLfloat scaleX{ 0.0f }, scaleY{ 0.0f }, scaleZ{ 0.0f };
	GLfloat minX{ 0.0f }, minY{ 0.0f }, minZ{ 0.0f };
	GLfloat maxX{ 0.0f }, maxY{ 0.0f }, maxZ{ 0.0f };
	GLfloat scaleAll{ 0.0f };
	GLfloat sizeX{ 0.0f }, sizeY{ 0.0f }, sizeZ{ 0.0f };

	FILE* objFile;

	fopen_s(&objFile, objName, "rb");

	if (NULL == objFile) {
		std::cerr << "Cannot file open!" << "\n";
		assert(false);
		return;
	}
	while (true) {
		GLchar lineHeader[50000];
		GLint res = fscanf(objFile, "%s", lineHeader);

		if (EOF == res)
			break;

		if (0 == strcmp(lineHeader, "v")) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			tempVertices.push_back(vertex);
		}
		else if (0 == strcmp(lineHeader, "vt")) {
			glm::vec2 uv;
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			tempUvs.push_back(uv);
		}
		else if (0 == strcmp(lineHeader, "vn")) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (0 == strcmp(lineHeader, "f")) {
			std::string vertex1, vertex2, vertex3;
			GLuint vertexIndex[3], uvIndex[3], normalIndex[3];
			// vertex uv normal
			int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (9 != matches) {
				std::cerr << "File can't be read by our simple parser : ( Try exporting with other options )" << "\n";
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = maxX - minX;
	scaleY = maxY - minY;
	scaleZ = maxZ - minZ;

	glm::vec3 temp;

	for (size_t i = 0; i < vertexIndices.size(); ++i) {
		GLuint vertexIndex = vertexIndices[i];
		temp = tempVertices[vertexIndex - 1];
		temp.x = temp.x - minX;
		temp.y = temp.y - minY;
		temp.z = temp.z - minZ;

		temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
		temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
		temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

		verticies.push_back(temp);
	}

	for (size_t i = 0; i < uvIndices.size(); ++i) {
		GLuint uvIndex = uvIndices[i];
		glm::vec2 vertex = tempUvs[uvIndex - 1];
		uvs.push_back(vertex);
	}

	for (size_t i = 0; i < normalIndices.size(); ++i) {
		GLuint normalIndex = normalIndices[i];
		glm::vec3 vertex = tempNormals[normalIndex - 1];
		normals.push_back(vertex);
	}

	for (size_t i = 0; i < verticies.size(); ++i) {
		colors.push_back(glm::vec3{ 1.0f,1.0f,1.0f });
	}
}

void Porsche::inputKeyboard(unsigned char key, int x, int y)
{
}

void Porsche::inputSpecialKeyboard(int key, int x, int y)
{
}

void Porsche::inputMouse(int button, int state, int x, int y)
{
}

void Porsche::update()
{
	if (collisionCount >= 3) {
		collisionCount = 0;
		SceneManager::getInstance()->changeScene(SceneManager::SceneType::FAIL);
		BackGround::getInstance()->setBGType(BackGround::BGType::FAIL);
	}

	switch (SceneManager::getInstance()->getCurrentSceneType())
	{
	case SceneManager::SceneType::SELECT:
		rotationDegree += 1.0f;
		break;
	case SceneManager::SceneType::PLAY:
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (speed <= 0.3f)
				speed += 0.01f;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (speed >= -0.2f)
				speed -= 0.01f;
		}
		else {
			if (speed < 0) {
				speed += 0.001f;
				if (speed >= 0)
					speed = 0;
			}
			else {
				speed -= 0.001f;
				if (speed <= 0)
					speed = 0;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (positionVector.x + 1.0f <= 8.0f) {
				if (rotationDegree >= -20.f) {
					rotationDegree -= 1.f;
				}
				positionVector.x += 0.1f;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (positionVector.x - 1.0f >= -8.0f) {
				if (rotationDegree <= 20.f) {
					rotationDegree += 1.f;
				}
				positionVector.x -= 0.1f;
			}
		}
		else {
			rotationDegree = 0.f;
		}
		positionVector.z -= speed;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			onJump = true;
		}

		if (onJump) {
			if (jumpVelocity > 0.0f)
				jumpForce = (0.5f * mass * powf(jumpVelocity, 2));
			else
				jumpForce = -(0.5f * mass * powf(jumpVelocity, 2));

			positionVector.y += jumpForce;
			jumpVelocity -= 0.1f;

			if (positionVector.y < 0.5f) {
				onJump = false;
				jumpVelocity = 2.0f;
			}
		}

		if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
			if (speed < 0.8f)
				speed += 0.01f;
		}
		else {
			if (speed >= 0.3f)
				speed -= 0.01f;
		}

		Camera::getInstance()->getPositionVector().z -= speed;
		Camera::getInstance()->getLookVector().z -= speed;
		Light::getInstance()->getPosition().z -= speed;
		break;
	default:
		break;
	}

}

void Porsche::render()
{
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 transformMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationDegree), glm::vec3{ 0.0f,1.0f,0.0f });
	translationMatrix = glm::translate(translationMatrix, positionVector);
	scaleMatrix = glm::scale(scaleMatrix, scaleVector);
	transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
	GLuint transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, verticies.size());

}

void Porsche::release()
{
}

void Porsche::collide()
{
	Sound::getInstance()->play(Sound::SoundType::COLLISION);
	speed = 0.0f;
	rotationDegree = 0;
}

GLint& Porsche::getCollisionCount() { return collisionCount; }
