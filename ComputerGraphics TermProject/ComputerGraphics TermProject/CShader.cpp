#include "CShader.h"

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <string>

void CShader::CreateShaderObject(GLuint * shader, GLuint nType, const GLchar * filename)
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

	glGenBuffers(glm::min((GLuint)LAYOUT_UV, nLayoutSize), VBO);

	if (pBuf == nullptr)
		return;

	for (int i = 0; i < glm::min((GLuint)LAYOUT_UV, nLayoutSize); ++i) {
		BindVBO(pBuf[i], VBO, i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}
}

GLubyte* CShader::LoadDIBitmap(const char* filename, BITMAPINFO** info) {
	FILE* fp; GLubyte* bits; int bitsize, infosize; BITMAPFILEHEADER header; // 바이너리읽기모드로파일을연다 

	fopen_s(&fp, filename, "rb");
	if (!fp)
		return NULL; // 비트맵파일헤더를읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	} // 파일이BMP 파일인지확인한다. 
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	} // BITMAPINFOHEADER 위치로간다. 
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER); // 비트맵이미지데이터를넣을메모리할당을한다. 
	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp);
		return NULL;
	}// 비트맵인포헤더를읽는다. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info); fclose(fp);
		return NULL;
	} // 비트맵의크기설정 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth * (*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// 비트맵의크기만큼메모리를할당한다. 
	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info); fclose(fp);
		return NULL;
	} // 비트맵데이터를bit(GLubyte 타입)에저장한다. 
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

void CShader::InitTexture(std::vector<const char*> files, std::vector<std::pair<int, int>> textureSize) {
	int count = 0;
	for (auto iter : files) {
		texture.emplace_back(0);
		BITMAPINFO* bmp;
		glGenTextures(1, &texture[count]);
		glBindTexture(GL_TEXTURE_2D, texture[count]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		void* data = LoadDIBitmap(iter, &bmp);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSize[count].first, textureSize[count].second, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		count++;

		if (data != NULL)
			delete bmp;
	}


	for (int i = 0; i < texture.size(); ++i) {
		std::string s;
		s.append("texture");
		s.push_back(i + 49);


		int tLocation = glGetUniformLocation(glShaderProgramID, s.c_str());
		glUniform1i(tLocation, i);
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
	switch (nLayoutSize) {
		// vertex - color - normal
	case LAYOUT_NORMAL:
		CreateShaderObject(&vertexshader, GL_VERTEX_SHADER, "./shader/shader_light.glvs");
		if (!PrintShaderError(&vertexshader, GL_VERTEX_SHADER))
			return;

		CreateShaderObject(&fragmentshader, GL_FRAGMENT_SHADER, "./shader/shader_light.glfs");
		if (!PrintShaderError(&fragmentshader, GL_FRAGMENT_SHADER))
			return;
		break;
		// vertex - color - normal - uv
	case LAYOUT_UV:
		CreateShaderObject(&vertexshader, GL_VERTEX_SHADER, "./shader/shader_texture.glvs");
		if (!PrintShaderError(&vertexshader, GL_VERTEX_SHADER))
			return;

		CreateShaderObject(&fragmentshader, GL_FRAGMENT_SHADER, "./shader/shader_texture.glfs");
		if (!PrintShaderError(&fragmentshader, GL_FRAGMENT_SHADER))
			return;
		break;
	case LAYOUT_UI:
		CreateShaderObject(&vertexshader, GL_VERTEX_SHADER, "./shader/shader_ui.glvs");
		if (!PrintShaderError(&vertexshader, GL_VERTEX_SHADER))
			return;

		CreateShaderObject(&fragmentshader, GL_FRAGMENT_SHADER, "./shader/shader_ui.glfs");
		if (!PrintShaderError(&fragmentshader, GL_FRAGMENT_SHADER))
			return;
		break;
	}

	// fragment shader 생성
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
	glDeleteBuffers(glm::min((GLuint)LAYOUT_UV, nLayoutSize), VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(glShaderProgramID);
	delete VBO;
}

CShader::CShader(GLuint layoutSize, CCamera& cam, glm::mat4 proj, std::vector<glm::vec3>* pBuf, std::vector<const char*> textureFiles, std::vector<std::pair<int, int>> textureSize) : nLayoutSize(layoutSize), camera(cam), Projection(proj)
{
	InitShaderProgram();
	if (nLayoutSize >= LAYOUT_UV)
		InitTexture(textureFiles, textureSize);

	VAO = 0;
	VBO = new GLuint[glm::min((GLuint)LAYOUT_UV, nLayoutSize)]{ 0 };
	if (pBuf != nullptr)
		CreateVAO(pBuf);
}

void CShader::DrawObject(std::vector<GLuint>& pIndex, GLuint DrawType)
{
	// 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(glShaderProgramID);
	// 사용할 VAO 불러오기
	glBindVertexArray(VAO);
	// 텍스쳐 불러오기

	if (nLayoutSize >= LAYOUT_UV) {
		for (int i = 0; i < texture.size(); ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
		}
	}
	// 삼각형 그리기
	glDrawElements(DrawType, pIndex.size(), GL_UNSIGNED_INT, &pIndex[0]);
}

void CShader::Update(glm::mat4 world, std::vector<glm::vec3>* pBuf, glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	glUseProgram(glShaderProgramID);
	glm::mat4 mul = Projection * camera.GetCameraProj() * world;

	int matTransformLocation = glGetUniformLocation(glShaderProgramID, "mat_Transform");
	glUniformMatrix4fv(matTransformLocation, 1, GL_FALSE, &mul[0][0]);

	int viewPosLocation = glGetUniformLocation(glShaderProgramID, "viewPos");
	glUniform3fv(viewPosLocation, 1, &camera.GetEye()[0]);

	int lightPosLocation = glGetUniformLocation(glShaderProgramID, "lightPos");
	glUniform3fv(lightPosLocation, 1, &lightPos[0]);

	int lightColorLocation = glGetUniformLocation(glShaderProgramID, "lightColor");
	glUniform3fv(lightColorLocation, 1, &lightColor[0]);

	int lightPowerLocation = glGetUniformLocation(glShaderProgramID, "lightPower");
	glUniform1f(lightPowerLocation, lightPower);

	glBindVertexArray(VAO);
	for (int i = 0; i < glm::min((GLuint)LAYOUT_UV, nLayoutSize); ++i) {
		BindVBO(pBuf[i], VBO, i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}
}

void CShader::Update(glm::mat4 world, std::vector<glm::vec3>* pBuf, std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower)
{
	glUseProgram(glShaderProgramID);
	glm::mat4 mul = Projection * camera.GetCameraProj() * world;

	int matTransformLocation = glGetUniformLocation(glShaderProgramID, "mat_Transform");
	glUniformMatrix4fv(matTransformLocation, 1, GL_FALSE, &mul[0][0]);

	int viewPosLocation = glGetUniformLocation(glShaderProgramID, "viewPos");
	glUniform3fv(viewPosLocation, 1, &camera.GetEye()[0]);

	int lightPosLocation = glGetUniformLocation(glShaderProgramID, "lightPos");
	glUniform3fv(lightPosLocation, 4, &lightPos[0][0]);

	int lightColorLocation = glGetUniformLocation(glShaderProgramID, "lightColor");
	glUniform3fv(lightColorLocation, 4, &lightColor[0][0]);

	int lightPowerLocation = glGetUniformLocation(glShaderProgramID, "lightPower");
	glUniform1fv(lightPowerLocation, 4, &lightPower[0]);

	glBindVertexArray(VAO);
	for (int i = 0; i < glm::min((GLuint)LAYOUT_UV, nLayoutSize); ++i) {
		BindVBO(pBuf[i], VBO, i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}
}

void CShader::Update(glm::vec3 bgColor, glm::mat4 world, std::vector<glm::vec3>* pBuf)
{
	glUseProgram(glShaderProgramID);
	glm::mat4 mul = Projection * camera.GetCameraProj() * world;

	int matTransformLocation = glGetUniformLocation(glShaderProgramID, "mat_Transform");
	glUniformMatrix4fv(matTransformLocation, 1, GL_FALSE, &mul[0][0]);

	int viewPosLocation = glGetUniformLocation(glShaderProgramID, "viewPos");
	glUniform3fv(viewPosLocation, 1, &camera.GetEye()[0]);

	int bgColorLocation = glGetUniformLocation(glShaderProgramID, "bgColor");
	glUniform3f(bgColorLocation, bgColor.r, bgColor.g, bgColor.b);

	glBindVertexArray(VAO);
	for (int i = 0; i < glm::min((GLuint)LAYOUT_UV, nLayoutSize); ++i) {
		BindVBO(pBuf[i], VBO, i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}
}

void CShader::UseProgram()
{
	glUseProgram(glShaderProgramID);
}