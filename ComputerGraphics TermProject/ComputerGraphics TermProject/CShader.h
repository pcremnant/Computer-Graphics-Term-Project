#pragma once
#include "define.h"
#include "CCamera.h"

class CShader {
private:
	GLuint glShaderProgramID;
	GLuint VAO;
	GLuint* VBO;
	GLuint nLayoutSize;

	void CreateShaderObject(GLuint* shader, GLuint nType, const GLchar* filename);
	char* filetobuf(const char* file);
	bool PrintShaderError(GLuint* shader, GLuint nType);
	void CreateVAO(std::vector<glm::vec3>* pBuf);
	GLuint BindVBO(std::vector<glm::vec3>& pBuffer, GLuint* VBO = nullptr, GLuint VBONumber = 0);
	void InitShaderProgram();


public:
	CShader(GLuint layoutSize, std::vector<glm::vec3>* pBuf);
	~CShader();
	void DrawObject(std::vector<GLuint>& pIndex, GLuint DrawType = GL_TRIANGLES);
	void Update(glm::mat4 world, CCamera& camera, glm::mat4 mat_Projection, std::vector<glm::vec3>* pBuf = nullptr, glm::vec3* lightPos = nullptr, glm::vec3* lightColor = nullptr);
	void UseProgram();
};