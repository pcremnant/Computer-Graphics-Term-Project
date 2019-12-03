#include "CShader.h"

void CShader::CreateShaderObject(GLuint* shader, GLuint nType, const GLchar* filename)
{
	GLchar* shadersource;
	shadersource = filetobuf(filename);
	*shader = glCreateShader(nType);
	glShaderSource(*shader, 1, (const GLchar * *)& shadersource, 0);
	glCompileShader(*shader);
	free(shadersource);
}
// 파일에서 코드 읽어서 반환
char* CShader::filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fopen_s(&fptr, file, "rb");
	if (!fptr)							// Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END);			// Seek to the end of the file
	length = ftell(fptr);				// Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1);	// Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET);			// Go back to the beginning of the file
	fread(buf, length, 1, fptr);		// Read the contents of the file in to the buffer
	fclose(fptr);						// Close the file
	buf[length] = 0;					// Null terminator

	return buf;							// Return the buffer
}
// 쉐이더 컴파일 에러 출력
bool CShader::PrintShaderError(GLuint* shader, GLuint nType)
{
	GLint IsCompiled;
	char* shaderInfoLog;
	GLint maxLength;

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &IsCompiled);
	if (IsCompiled == FALSE)
	{
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);
		shaderInfoLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(*shader, maxLength, &maxLength, shaderInfoLog);

		std::cerr << "ERROR: shader program 연결 실패" << std::endl;
		if (nType == GL_FRAGMENT_SHADER)
			std::cout << "glfs: ";
		else if (nType == GL_VERTEX_SHADER)
			std::cout << "glvs: ";
		std::cout << shaderInfoLog << std::endl;
		std::free(shaderInfoLog);
		return false;
	}
	return true;
}
// VAO 생성
void CShader::CreateVAO(std::vector<glm::vec3>* pBuf)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(nLayoutSize, VBO);

	if (pBuf == nullptr)
		return;

	for (int i = 0; i < nLayoutSize; ++i) {
		BindVBO(pBuf[i], VBO, i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}
}
// VBO 바인딩
GLuint CShader::BindVBO(std::vector<glm::vec3>& pBuffer, GLuint* VBO, GLuint VBONumber)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VBONumber]);
	glBufferData(GL_ARRAY_BUFFER, pBuffer.size() * sizeof(glm::vec3), &pBuffer[0], GL_DYNAMIC_DRAW);

	return VBO[VBONumber];
}

void CShader::InitShaderProgram()
{
	GLuint vertexshader, fragmentshader;

	// vertex shader 생성
	CreateShaderObject(&vertexshader, GL_VERTEX_SHADER, "shader.glvs");
	if (!PrintShaderError(&vertexshader, GL_VERTEX_SHADER))
		return;

	// fragment shader 생성
	CreateShaderObject(&fragmentshader, GL_FRAGMENT_SHADER, "shader.glfs");
	if (!PrintShaderError(&fragmentshader, GL_FRAGMENT_SHADER))
		return;

	glShaderProgramID = glCreateProgram();
	glAttachShader(glShaderProgramID, vertexshader);
	glAttachShader(glShaderProgramID, fragmentshader);

	glLinkProgram(glShaderProgramID);

	GLint IsLinked;
	GLint maxLength;
	char* shaderProgramInfoLog;

	glGetProgramiv(glShaderProgramID, GL_LINK_STATUS, &IsLinked);
	if (IsLinked == FALSE)
	{
		glGetProgramiv(glShaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);
		shaderProgramInfoLog = (char*)malloc(maxLength);
		glGetProgramInfoLog(glShaderProgramID, maxLength, &maxLength,
			shaderProgramInfoLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << shaderProgramInfoLog << std::endl;
		free(shaderProgramInfoLog);
		return;
	}

	glUseProgram(glShaderProgramID);
}

CShader::~CShader()
{
	glDeleteBuffers(nLayoutSize, VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(glShaderProgramID);
	delete VBO;
}

CShader::CShader(GLuint layoutSize, std::vector<glm::vec3>* pBuf) : nLayoutSize(layoutSize)
{
	InitShaderProgram();
	VAO = 0;
	VBO = new GLuint[nLayoutSize]{ 0 };
	if (pBuf != nullptr)
		CreateVAO(pBuf);
}

void CShader::DrawObject(std::vector<GLuint>& pIndex, GLuint DrawType)
{
	// 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(glShaderProgramID);
	// 사용할 VAO 불러오기
	glBindVertexArray(VAO);
	// 삼각형 그리기
	glDrawElements(DrawType, pIndex.size(), GL_UNSIGNED_INT, &pIndex[0]);
}

void CShader::Update(glm::mat4 world, CCamera& camera, glm::mat4 mat_Projection, std::vector<glm::vec3>* pBuf, glm::vec3* lightPos, glm::vec3* lightColor)
{
	glUseProgram(glShaderProgramID);
	glm::mat4 mul = mat_Projection * camera.GetCameraProj() * world;

	int matTransformLocation = glGetUniformLocation(glShaderProgramID, "mat_Transform");
	glUniformMatrix4fv(matTransformLocation, 1, GL_FALSE, &mul[0][0]);

	int viewPosLocation = glGetUniformLocation(glShaderProgramID, "viewPos");
	glUniform3fv(viewPosLocation, 1, &camera.GetEye()[0]);

	int lightPosLocation = glGetUniformLocation(glShaderProgramID, "lightPos");
	if (lightPos == nullptr) {
		glm::vec3 lightNone = glm::vec3{ 0,0,0 };
		glUniform3fv(lightPosLocation, 1, &lightNone[0]);
	}
	else {
		glm::vec3 lightNone = *lightPos;
		glUniform3fv(lightPosLocation, 1, &lightNone[0]);
	}

	int lightColorLocation = glGetUniformLocation(glShaderProgramID, "lightColor");
	if (lightColor == nullptr) {
		glm::vec3 lightNone = glm::vec3{ 1,1,1 };
		glUniform3fv(lightColorLocation, 1, &lightNone[0]);
	}
	else {
		glm::vec3 lightNone = *lightColor;
		glUniform3fv(lightColorLocation, 1, &lightNone[0]);
	}

	glBindVertexArray(VAO);
	for (int i = 0; i < nLayoutSize; ++i) {
		BindVBO(pBuf[i], VBO, i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}
}

void CShader::UseProgram()
{
	glUseProgram(glShaderProgramID);
}