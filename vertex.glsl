#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vColor;

out vec3 FragPos; // location = 0
out vec3 Normal; // location = 1
out vec2 TexCoord; // location = 2
out vec3 Color; // �����׸�Ʈ ���̴����� ���� , location = 3

uniform mat4 modelTransform; // �𵨸� ��ȯ��
uniform mat4 viewTransform; // ���� ��ȯ��
uniform mat4 projectionTransform; // ���� ��ȯ��

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos,1.0);
	FragPos = vec3(modelTransform * vec4(vPos,1.0));
	Normal = mat3(transpose(inverse(modelTransform))) * vNormal;
	TexCoord = vTexCoord;
	Color = vColor; // ��ü ���� ���� 
}