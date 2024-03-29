#pragma once
#include "define.h"
#include "CCamera.h"

class CShader {
private:
	GLuint glShaderProgramID;
	GLuint VAO;
	GLuint* VBO;
	GLuint nLayoutSize;

	std::vector<unsigned int> texture;

	CCamera& camera;
	glm::mat4 Projection;


	GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info);
	void InitTexture(std::vector<const char*> files, std::vector<std::pair<int, int>> textureSize);

	void CreateShaderObject(GLuint* shader, GLuint nType, const GLchar* filename);
	char* filetobuf(const char* file);
	bool PrintShaderError(GLuint* shader, GLuint nType);
	void CreateVAO(std::vector<glm::vec3>* pBuf);
	GLuint BindVBO(std::vector<glm::vec3>& pBuffer, GLuint* VBO = nullptr, GLuint VBONumber = 0);
	void InitShaderProgram();

public:
	CShader(GLuint layoutSize, CCamera& cam, int);
	CShader(GLuint layoutSize, CCamera& cam, glm::mat4 proj = glm::mat4{ 1.0f }, std::vector<glm::vec3>* pBuf = nullptr, std::vector<const char*> textureFiles = std::vector<const char*>(), std::vector<std::pair<int, int>> textureSize = std::vector<std::pair<int, int>>());
	~CShader();
	void DrawObject(std::vector<GLuint>& pIndex, GLuint DrawType = GL_TRIANGLES);
	// 조명 1개일 때 부르는 업데이트
	void Update(glm::mat4 world, std::vector<glm::vec3>* pBuf = nullptr, glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f, glm::vec3 bgColor = glm::vec3{ 1,1,1 });
	// 조명 여러개일 때 부르는 업데이트
	void Update(glm::mat4 world, std::vector<glm::vec3>* pBuf = nullptr, std::vector<glm::vec3> lightPos = std::vector<glm::vec3>(), std::vector<glm::vec3> lightColor = std::vector<glm::vec3>(), std::vector<float> lightPower = std::vector<float>(), glm::vec3 bgColor = glm::vec3{ 1,1,1 });
	// UI 로딩시 부르는 업데이트
	void Update(glm::vec3 bgColor = glm::vec3{ 1,1,1 }, glm::mat4 world = glm::mat4{ 1.0, }, std::vector<glm::vec3>* pBuf = nullptr);
	// 인게임 UI 로딩시 부르는 업데이트
	void Update(glm::vec3 bgColor = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, std::vector<glm::vec3>* pBuf = nullptr);
	void UseProgram();
	void ChangeFov(glm::mat4 proj);
	inline const GLuint get_glShaderProgramID()const { return glShaderProgramID; }
};