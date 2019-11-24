#pragma once
#include "define.h"

class CShader {
private:
	GLuint glShaderProgramID;
	GLuint VAO;
	GLuint* VBO;
	GLuint nLayoutSize;

	void CreateShaderObject(GLuint* shader, GLuint nType, const GLchar* filename);
	char* filetobuf(const char* file);
	bool PrintShaderError(GLuint* shader, GLuint nType);
	void CreateVAO(vec3Buffer* pBuf);
	GLuint CreateVec3VBO(vec3Buffer& pBuffer, GLuint* VBO = nullptr, GLuint VBONumber = 0);
	void InitShaderProgram();


public:
	CShader(GLuint layoutSize, vec3Buffer* pBuf);
	void DrawObject(std::vector<GLuint>& pIndex, GLuint DrawType = GL_TRIANGLES);
	void Update(glm::mat4 world, glm::mat4 camera, glm::mat4 mat_Projection, vec3Buffer* pBuf = nullptr);
	void UseProgram();
};