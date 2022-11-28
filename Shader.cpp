#include "Shader.h"

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
	//if (nullptr != CarManager::getInstance()->currentCar) {
	//	glDeleteVertexArrays(1, &(CarManager::getInstance()->currentCar->vao));
	//	glDeleteBuffers(1, &(CarManager::getInstance()->currentCar->vertexVbo));
	//	glDeleteBuffers(1, &(CarManager::getInstance()->currentCar->normalVbo));
	//	glDeleteBuffers(1, &(CarManager::getInstance()->currentCar->colorVbo));
	//}
	//
	//glGenVertexArrays(1, &(CarManager::getInstance()->currentCar->vao));
	//glGenBuffers(1, &(CarManager::getInstance()->currentCar->vertexVbo));
	//glGenBuffers(1, &(CarManager::getInstance()->currentCar->normalVbo));
	//glGenBuffers(1, &(CarManager::getInstance()->currentCar->colorVbo));

	for (size_t i = 0; i < 2; ++i) {
		glGenVertexArrays(1, &(CarManager::getInstance()->cars[i]->vao));
		glGenBuffers(1, &(CarManager::getInstance()->cars[i]->vertexVbo));
		glGenBuffers(1, &(CarManager::getInstance()->cars[i]->normalVbo));
		glGenBuffers(1, &(CarManager::getInstance()->cars[i]->colorVbo));
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

void Shader::initBuffer()
{
	// Car
	{
		for (size_t i = 0; i < 2; ++i) {
			glBindVertexArray(CarManager::getInstance()->cars[i]->vao);
			glBindBuffer(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->vertexVbo);
			glBufferData(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->verticies.size() * sizeof(glm::vec3), CarManager::getInstance()->cars[i]->verticies.data(), GL_STATIC_DRAW);
			GLuint pAttribute = glGetAttribLocation(Shader::getInstance()->getShaderProgram(), "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->normalVbo);
			glBufferData(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->normals.size() * sizeof(glm::vec3), CarManager::getInstance()->cars[i]->normals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(Shader::getInstance()->getShaderProgram(), "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->colorVbo);
			glBufferData(GL_ARRAY_BUFFER, CarManager::getInstance()->cars[i]->colors.size() * sizeof(glm::vec3), CarManager::getInstance()->cars[i]->colors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(Shader::getInstance()->getShaderProgram(), "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}
		GLuint lightPosLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "lightPos"); // lightPos 전달 
		glUniform3f(lightPosLocation, Light::getInstance()->getPosition().x, Light::getInstance()->getPosition().y, Light::getInstance()->getPosition().z);
		GLuint lightColorLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "lightColor"); // lightColor 전달 
		glUniform3f(lightColorLocation, Light::getInstance()->getLightColor().x, Light::getInstance()->getLightColor().y, Light::getInstance()->getLightColor().z);
		GLuint viewPosLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewPos"); // viewPos 값 전달: 카메라 위치 
		glUniform3f(viewPosLocation, Camera::getInstance()->getPositionVector().x, Camera::getInstance()->getPositionVector().y, Camera::getInstance()->getPositionVector().z);
	}

	// Light

}

void Shader::release()
{

}
