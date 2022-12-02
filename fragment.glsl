#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in vec3 Color;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D outTexture;

void main()
{
	// ambient
	float ambientLight = 0.3; // �ֺ� ���� ���
	vec3 ambient = ambientLight * lightColor; // �ֺ� ���� ��

	// Diffuse
	vec3 normalVector = normalize(Normal); // �븻 ����ȭ
	vec3 lightDir = normalize(lightPos - FragPos); // ǥ��� ������ ��ġ�� ���� ���� ����
	float diffuseLight = max(dot(normalVector,lightDir),0.0); // N�� L�� ���� ������ ���� ���� (���� �� X)
	vec3 diffuse = diffuseLight * lightColor; // ����ݻ� ���� �� = ����ݻ簪 * �������

	// Specular
	int shininess = 128; // ���� ��� 
	vec3 viewDir = normalize(viewPos - FragPos); // ������ ����
	vec3 reflectDir = reflect(-lightDir,normalVector); // �ݻ� ����: reflect �Լ� - �Ի� ������ �ݻ� ���� ���
	float specularLight = max(dot(viewDir,reflectDir),0.0); // V�� R�� ���������� ���� ����: ���� ���� 
	specularLight = pow(specularLight,shininess); // shininess ���� ���־� ���̶���Ʈ ����� ��
	vec3 specular = specularLight * lightColor; // �ſ� �ݻ� ����: �ſ�ݻ簪 * ������� 

	vec3 result = (ambient + diffuse + specular) * Color; // ���� ���� ������ �ȼ� ����: (�ֺ�+����ݻ�+�ſ�ݻ�����) * ��ü���� 

	FragColor =  vec4(result,1.0f) * texture(outTexture,TexCoord);
}