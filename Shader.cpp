#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Shader* Shader::pInst = nullptr;

Shader::Shader()
{

}

Shader* Shader::getInstance()
{
	if (nullptr == pInst)
		pInst = new Shader;

	return pInst;
}

const GLuint& Shader::getShaderProgram() const
{
	return shaderProgram;
}

char* Shader::file2Buffer(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}

void Shader::makeVertexShader()
{
	vertexSource = file2Buffer("vertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, (const GLchar**)(&vertexSource), 0);

	glCompileShader(vertexShader);

	checkCompileError(vertexShader, "vertex");
}

void Shader::makeFragmentShader()
{
	fragmentSource = file2Buffer("fragment.glsl");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, (const GLchar**)(&fragmentSource), 0);

	glCompileShader(fragmentShader);

	checkCompileError(fragmentShader, "fragment");
}

void Shader::checkCompileError(const GLuint& shaderType, const char* name)
{
	GLint result;

	GLchar errorLog[512];

	glGetShaderiv(shaderType, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(shaderType, 512, NULL, errorLog);
		std::cerr << "ERROR:" << name << " complie Failed!\n" << errorLog << std::endl;
	}
}

void Shader::glGenerate()
{
	// BackGround
	glGenVertexArrays(1, &(BackGround::getInstance()->vao));
	glGenBuffers(1, &(BackGround::getInstance()->vertexVbo));
	glGenBuffers(1, &(BackGround::getInstance()->normalVbo));
	glGenBuffers(1, &(BackGround::getInstance()->colorVbo));
	glGenBuffers(1, &(BackGround::getInstance()->uvVbo));
	glGenTextures(4, (BackGround::getInstance()->textures));

	// Cars
	for (size_t i = 0; i < CarManager::getInstance()->nCar; ++i) {
		glGenVertexArrays(1, &(CarManager::getInstance()->cars[i]->vao));
		glGenBuffers(1, &(CarManager::getInstance()->cars[i]->vertexVbo));
		glGenBuffers(1, &(CarManager::getInstance()->cars[i]->normalVbo));
		glGenBuffers(1, &(CarManager::getInstance()->cars[i]->colorVbo));
		glGenBuffers(1, &(CarManager::getInstance()->cars[i]->uvVbo));
		glGenTextures(1, &(CarManager::getInstance()->cars[i]->texture));
	}
	
	// Map
	for (size_t i = 0; i < StageManager::getInstance()->nRoads; ++i) {
		glGenVertexArrays(1, &(StageManager::getInstance()->roads[i]->vao));
		glGenBuffers(1, &(StageManager::getInstance()->roads[i]->vertexVbo));
		glGenBuffers(1, &(StageManager::getInstance()->roads[i]->normalVbo));
		glGenBuffers(1, &(StageManager::getInstance()->roads[i]->colorVbo));
		glGenBuffers(1, &(StageManager::getInstance()->roads[i]->uvVbo));
		glGenTextures(1, &(StageManager::getInstance()->roads[i]->texture));
	}

	// Obstacles
	for (auto& ele : StageManager::getInstance()->obstacles) {
		glGenVertexArrays(1, &(ele)->vao);
		glGenBuffers(1, &(ele)->vertexVbo);
		glGenBuffers(1, &(ele)->normalVbo);
		glGenBuffers(1, &(ele)->colorVbo);
		glGenBuffers(1, &(ele)->uvVbo);
		glGenTextures(1, &(ele)->texture);
	}

	// Particles
	for (auto& element : ParticleManager::getInstance()->particles) {
		glGenVertexArrays(1, &(element)->vao);
		glGenBuffers(1, &(element)->vertexVbo);
		glGenBuffers(1, &(element)->normalVbo);
		glGenBuffers(1, &(element)->colorVbo);
		glGenBuffers(1, &(element)->uvVbo);
		glGenTextures(1, &(element)->texture);
	}
}

void Shader::initShader()
{
	makeVertexShader();
	makeFragmentShader();

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkCompileError(shaderProgram, "shader program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
}

void Shader::initTexture()
{
	// BackGround
	{
		for (size_t i = 0; i < 4; ++i) {
			int imageWidth, imageHeight, numberOfChannel;
			glBindTexture(GL_TEXTURE_2D, BackGround::getInstance()->textures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data;
			switch (i)
			{
			case 0:
				data = stbi_load("Resources/BackGround/title.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			case 1:
				data = stbi_load("Resources/BackGround/select.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			case 2:
				data = stbi_load("Resources/BackGround/select.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			case 3:
				data = stbi_load("Resources/BackGround/end.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			default:
				break;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}

	// Car
	{
		for (size_t i = 0; i < CarManager::getInstance()->nCar; ++i) {
			int imageWidth, imageHeight, numberOfChannel;
			glBindTexture(GL_TEXTURE_2D, CarManager::getInstance()->cars[i]->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = nullptr;
			switch (i)
			{
			case 0:
			{
				data = stbi_load("Resources/Car/FORD/0000.bmp", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			}
			case 1:
				data = stbi_load("Resources/Car/PORSCHE/0000.bmp", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			case 2:
				data = stbi_load("Resources/Car/FORD/0000.bmp", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			default:
				break;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}

	// Road
	{
		for (size_t i = 0; i < StageManager::getInstance()->nRoads; ++i) {
			int imageWidth, imageHeight, numberOfChannel;
			glBindTexture(GL_TEXTURE_2D, StageManager::getInstance()->roads[i]->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load("Resources/Map/road.jpg", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}

	// Obstacles

	{
		for (auto& ele : StageManager::getInstance()->obstacles) {
			int imageWidth, imageHeight, numberOfChannel;
			glBindTexture(GL_TEXTURE_2D, ele->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load("Resources/Map/box.jpg", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}

	// Particles
	{
		for (auto& element : ParticleManager::getInstance()->particles) {
			int imageWidth, imageHeight, numberOfChannel;
			glBindTexture(GL_TEXTURE_2D, element->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_set_flip_vertically_on_load(true);
			std::mt19937 mersenne{ std::random_device{}() };
			std::uniform_int_distribution<GLint> randomColor{ 0,3 };
			unsigned char* data = nullptr;
			switch (randomColor(mersenne))
			{
			case 0:
				data = stbi_load("Resources/Particle/color00.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			case 1:
				data = stbi_load("Resources/Particle/color01.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			case 2:
				data = stbi_load("Resources/Particle/color02.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			case 3:
				data = stbi_load("Resources/Particle/color03.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
				break;
			default:
				break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}
}

void Shader::initBuffer()
{
	// BackGround
	{
		glBindVertexArray(BackGround::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, BackGround::getInstance()->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, BackGround::getInstance()->verticies.size() * sizeof(glm::vec3), BackGround::getInstance()->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, BackGround::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, BackGround::getInstance()->normals.size() * sizeof(glm::vec3), BackGround::getInstance()->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, BackGround::getInstance()->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, BackGround::getInstance()->colors.size() * sizeof(glm::vec3), BackGround::getInstance()->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);


		glBindBuffer(GL_ARRAY_BUFFER, BackGround::getInstance()->uvVbo);
		glBufferData(GL_ARRAY_BUFFER, BackGround::getInstance()->uvs.size() * sizeof(glm::vec2), BackGround::getInstance()->uvs.data(), GL_STATIC_DRAW);
		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(tAttribute);
	}

	// Car
	{
		for (size_t i = 0; i < CarManager::getInstance()->nCar; ++i) {
			glBindVertexArray(CarManager::getInstance()->cars[i]->vao);
			glBindBuffer(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->vertexVbo);
			glBufferData(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->verticies.size() * sizeof(glm::vec3), CarManager::getInstance()->cars[i]->verticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->normalVbo);
			glBufferData(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->normals.size() * sizeof(glm::vec3), CarManager::getInstance()->cars[i]->normals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->colorVbo);
			glBufferData(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->colors.size() * sizeof(glm::vec3), CarManager::getInstance()->cars[i]->colors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->uvVbo);
			glBufferData(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->uvs.size() * sizeof(glm::vec2), CarManager::getInstance()->cars[i]->uvs.data(), GL_STATIC_DRAW);
			GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
			glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glEnableVertexAttribArray(tAttribute);
		}
	}

	// Map
	for (size_t i = 0; i < StageManager::getInstance()->nRoads; ++i) {
		glBindVertexArray(StageManager::getInstance()->roads[i]->vao);
		glBindBuffer(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->verticies.size() * sizeof(glm::vec3), StageManager::getInstance()->roads[i]->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->normals.size() * sizeof(glm::vec3), StageManager::getInstance()->roads[i]->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->colors.size() * sizeof(glm::vec3), StageManager::getInstance()->roads[i]->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->uvVbo);
		glBufferData(GL_ARRAY_BUFFER, StageManager::getInstance()->roads[i]->uvs.size() * sizeof(glm::vec2), StageManager::getInstance()->roads[i]->uvs.data(), GL_STATIC_DRAW);
		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(tAttribute);
	}

	// Obstacles
	for (auto& ele : StageManager::getInstance()->obstacles) {
		glBindVertexArray(ele->vao);
		glBindBuffer(GL_ARRAY_BUFFER, ele->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, ele->verticies.size() * sizeof(glm::vec3), ele->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, ele->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, ele->normals.size() * sizeof(glm::vec3), ele->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, ele->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, ele->colors.size() * sizeof(glm::vec3), ele->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, ele->uvVbo);
		glBufferData(GL_ARRAY_BUFFER, ele->uvs.size() * sizeof(glm::vec2), ele->uvs.data(), GL_STATIC_DRAW);
		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(tAttribute);
	}

	// Particles
	{
		for (auto& element : ParticleManager::getInstance()->particles) {
			glBindVertexArray(element->vao);
			glBindBuffer(GL_ARRAY_BUFFER, element->vertexVbo);
			glBufferData(GL_ARRAY_BUFFER, element->verticies.size() * sizeof(glm::vec3), element->verticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, element->normalVbo);
			glBufferData(GL_ARRAY_BUFFER, element->normals.size() * sizeof(glm::vec3), element->normals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, element->colorVbo);
			glBufferData(GL_ARRAY_BUFFER, element->colors.size() * sizeof(glm::vec3), element->colors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, element->uvVbo);
			glBufferData(GL_ARRAY_BUFFER, element->uvs.size() * sizeof(glm::vec2), element->uvs.data(), GL_STATIC_DRAW);
			GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
			glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glEnableVertexAttribArray(tAttribute);
		}
	}

	// Light
	GLuint lightPosLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "lightPos"); // lightPos 전달 
	glUniform3f(lightPosLocation, Light::getInstance()->getPosition().x, Light::getInstance()->getPosition().y, Light::getInstance()->getPosition().z);
	GLuint lightColorLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "lightColor"); // lightColor 전달 
	glUniform3f(lightColorLocation, Light::getInstance()->getLightColor().x, Light::getInstance()->getLightColor().y, Light::getInstance()->getLightColor().z);
	GLuint viewPosLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewPos"); // viewPos 값 전달: 카메라 위치 
	glUniform3f(viewPosLocation, Camera::getInstance()->getPositionVector().x, Camera::getInstance()->getPositionVector().y, Camera::getInstance()->getPositionVector().z);
}

void Shader::release()
{

}
