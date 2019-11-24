#pragma once
#include<gl/glew.h>
#include<GL/freeglut.h>
#include<gl/freeglut_ext.h>
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <random>
#include <fstream>

#define BUFFER_VERTEX 0							// pBuffer의 버텍스 인덱스
#define BUFFER_COLOR 1

#define WINDOW_X 100							// 윈도우 창 x 위치
#define WINDOW_Y 100							// 윈도우 창 y 위치
#define WINDOW_WIDTH 800						// 윈도우 창 너비
#define WINDOW_HEIGHT 600						// 윈도우 창 높이

typedef std::vector<glm::vec4> vec4Buffer;
typedef std::vector<glm::vec3> vec3Buffer;
typedef std::vector<glm::vec2> vec2Buffer;

// 윈도우 배경색
GLclampf cBackground_red = 1.0f;
GLclampf cBackground_green = 1.0f;
GLclampf cBackground_blue = 1.0f;

// 투영 방식
#define PROJ(fovy) glm::perspective(glm::radians(fovy), (float)800 / (float)600, 0.1f, 100.0f)
#define ORTHO glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.1f, 100.f)

// 색상 랜덤 설정
void SetRandomColor(GLclampf& r, GLclampf& g, GLclampf& b)
{
	std::random_device rnd;
	std::mt19937 rn(rnd());
	std::uniform_real_distribution<GLclampf> range(0, 1);

	r = range(rn), g = range(rn), b = range(rn);
}

class CCamera {
private:
	enum { CAMERA_EYE, CAMERA_AT, CAMERA_UP };

	glm::vec3 vDirection;
	GLfloat fAngle;

	vec3Buffer gCamera;
public:
	CCamera()
	{
		fAngle = 0;
		vDirection = { 0,0,-1 };
		gCamera.push_back({ 0, 0, 2 });
		gCamera.push_back({ 0, 0, 0 });
		gCamera.push_back({ 0, 1, 0 });
		UpdateCamera();

	}

	glm::vec3& GetEye() { return gCamera[CAMERA_EYE]; }
	glm::vec3& GetAt() { return gCamera[CAMERA_AT]; }
	glm::vec3& GetUp() { return gCamera[CAMERA_UP]; }
	vec3Buffer& GetCamera() { return gCamera; }
	glm::mat4 GetCameraProj() {
		glm::mat4 CameraMat = glm::lookAt(
			gCamera[CAMERA_EYE],
			gCamera[CAMERA_AT],
			gCamera[CAMERA_UP]
		);
		return CameraMat;
	}

	void UpdateCamera()
	{
		vDirection.x = glm::sin(fAngle);
		vDirection.z = -glm::cos(fAngle);

		gCamera[CAMERA_AT].x = gCamera[CAMERA_EYE].x + vDirection.x / 10.f;
		gCamera[CAMERA_AT].z = gCamera[CAMERA_EYE].z + vDirection.z / 10.f;
	}


	void Move(unsigned char key)
	{
		glm::vec3 tmpDirection;
		switch (key) {
		case 'w':
		case 'W':
			tmpDirection = { vDirection.x / 10,vDirection.y / 10,vDirection.z / 10 };
			gCamera[CAMERA_EYE] += tmpDirection;
			gCamera[CAMERA_AT] += tmpDirection;
			break;
		case 's':
		case 'S':
			tmpDirection = { vDirection.x / 10,vDirection.y / 10,vDirection.z / 10 };
			gCamera[CAMERA_EYE] -= tmpDirection;
			gCamera[CAMERA_AT] -= tmpDirection;
			break;
		case 'a':
		case 'A':
		{
			glm::mat4 scalling{ 0.1f };
			scalling[3][3] = 1.0;
			tmpDirection = scalling * glm::rotate(glm::radians(90.f), glm::vec3{ 0,1,0 }) * glm::vec4{ vDirection,1.0 };
			gCamera[CAMERA_EYE] += tmpDirection;
			gCamera[CAMERA_AT] += tmpDirection;
		}
		break;

		case 'd':
		case 'D': {
			glm::mat4 scalling{ 0.1f };
			scalling[3][3] = 1.0;
			tmpDirection = scalling * glm::rotate(glm::radians(-90.f), glm::vec3{ 0,1,0 }) * glm::vec4{ vDirection,1.0 };
			gCamera[CAMERA_EYE] += tmpDirection;
			gCamera[CAMERA_AT] += tmpDirection;
		}
				  break;
		case 'q':
		case 'Q':
			fAngle -= 0.05f;
			break;
		case 'e':
		case 'E':
			fAngle += 0.05f;
			break;
		case 'r':
		case 'R':
			tmpDirection = { 0,0.05,0 };
			gCamera[CAMERA_EYE] += tmpDirection;
			gCamera[CAMERA_AT] += tmpDirection;
			break;
		case 'f':
		case 'F':
			tmpDirection = { 0,0.05,0 };
			gCamera[CAMERA_EYE] -= tmpDirection;
			gCamera[CAMERA_AT] -= tmpDirection;
			break;
		case '1':
			fAngle = 0;
			vDirection = { 0,0,-1 };
			gCamera[CAMERA_EYE] = { 0, 0, 1 };
			gCamera[CAMERA_AT] = { 0, 0, 0 };
			gCamera[CAMERA_UP] = { 0, 1, 0 };

			for (int i = 0; i < 3; ++i)
				glm::normalize(gCamera[i]);
			break;
		}
		UpdateCamera();
	}
};



class CShader {
private:
	GLuint glShaderProgramID;
	GLuint VAO;
	GLuint* VBO;
	GLuint nLayoutSize;

	void CreateShaderObject(GLuint* shader, GLuint nType, const GLchar* filename)
	{
		GLchar* shadersource;
		shadersource = filetobuf(filename);
		*shader = glCreateShader(nType);
		glShaderSource(*shader, 1, (const GLchar * *)& shadersource, 0);
		glCompileShader(*shader);

	}
	// 파일에서 코드 읽어서 반환
	char* filetobuf(const char* file)
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
	bool PrintShaderError(GLuint* shader, GLuint nType)
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
	void CreateVAO(vec3Buffer* pBuf)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(nLayoutSize, VBO);

		if (pBuf == nullptr)
			return;

		for (int i = 0; i < nLayoutSize; ++i) {
			CreateVec3VBO(pBuf[i], VBO, i);
			glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(i);
		}
	}
	// VBO 생성
	GLuint CreateVec3VBO(vec3Buffer& pBuffer, GLuint* VBO = nullptr, GLuint VBONumber = 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO[VBONumber]);
		glBufferData(GL_ARRAY_BUFFER, pBuffer.size() * sizeof(glm::vec3), &pBuffer[0], GL_STATIC_DRAW);

		return VBO[VBONumber];
	}
	void InitShaderProgram()
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


public:
	CShader(GLuint layoutSize, vec3Buffer* pBuf) : nLayoutSize(layoutSize)
	{
		InitShaderProgram();
		VAO = 0;
		VBO = new GLuint[nLayoutSize]{ 0 };
		if (pBuf != nullptr)
			CreateVAO(pBuf);
	}

	void DrawObject(std::vector<GLuint>& pIndex, GLuint DrawType = GL_TRIANGLES)
	{
		// 렌더링 파이프라인에 세이더 불러오기
		glUseProgram(glShaderProgramID);
		// 사용할 VAO 불러오기
		glBindVertexArray(VAO);
		// 삼각형 그리기
		glDrawElements(DrawType, pIndex.size(), GL_UNSIGNED_INT, &pIndex[0]);
	}

	void Update(glm::mat4 world, glm::mat4 camera, glm::mat4 mat_Projection, vec3Buffer* pBuf = nullptr)
	{
		glUseProgram(glShaderProgramID);
		glm::mat4 mul = mat_Projection * camera * world;
		int matTransformLocation = glGetUniformLocation(glShaderProgramID, "mat_Transform");
		glUniformMatrix4fv(matTransformLocation, 1, GL_FALSE, &mul[0][0]);
		if (pBuf != nullptr)
			CreateVAO(pBuf);
	}
	void UseProgram()
	{
		glUseProgram(glShaderProgramID);
	}
};

class CModel {
protected:
	vec3Buffer gVertex;
	vec3Buffer gColor;
	vec2Buffer gUv;
	vec3Buffer gNormal;

	std::vector<GLuint> gIndex;

	GLuint nLayoutSize;
	GLuint nDrawType;
	bool bIsDraw;
public:
	CModel(GLuint drawtype = GL_TRIANGLES, GLuint layout = 2) : nLayoutSize(layout), nDrawType(drawtype) {}
	void SetObjectVertex(const char* ObjectFile)
	{
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		vec3Buffer temp_vertices;
		vec2Buffer temp_uvs;
		vec3Buffer temp_normals;

		std::ifstream readFile;
		readFile.open(ObjectFile);

		while (!readFile.eof()) {

			char lineHeader[128];
			readFile >> lineHeader;

			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				for (int i = 0; i < 3; ++i) {
					readFile >> vertex[i];
				}
				vertex.y -= 0.25;
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec3 uv;
				for (int i = 0; i < 2; ++i)
					readFile >> uv[i];
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				for (int i = 0; i < 3; ++i)
					readFile >> normal[i];
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex[3];
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				int i = 0;
				while (i < 9) {
					char temp;
					readFile >> vertexIndex[(int)i++ / 3];
					readFile >> temp;
					readFile >> uvIndex[(int)i++ / 3];
					readFile >> temp;
					readFile >> normalIndex[(int)i++ / 3];
				}
				gIndex.push_back(vertexIndex[0] - 1);
				gIndex.push_back(vertexIndex[1] - 1);
				gIndex.push_back(vertexIndex[2] - 1);
			}
		}
		GLclampf tmpColor = 0.0f;
		for (auto iter = temp_vertices.begin(); iter != temp_vertices.end(); ++iter) {
			gVertex.push_back(*iter);
			tmpColor += 1.f / (float)temp_vertices.size();
			gColor.push_back(glm::vec3{ tmpColor, });
		}

		readFile.close();
	}
	vec3Buffer& GetVertex() { return gVertex; }
	vec3Buffer& GetNormal() { return gNormal; }
	vec2Buffer& GetUv() { return gUv; }
	vec3Buffer& GetColor() { return gColor; }
	std::vector<GLuint>& GetIndex() { return gIndex; }
	GLuint& GetLayoutSize() { return nLayoutSize; }
	void SetDrawType(GLuint drawtype) { nDrawType = drawtype; }
	GLuint& GetDrawType() { return nDrawType; }
	bool& GetIsDraw() { return bIsDraw; }
};

class CCube : public CModel {
protected:
	float fSize;
public:
	CCube(glm::vec3 size = glm::vec3{ 1,1,1 }) : CModel(GL_TRIANGLES) {
		fSize = 0.5;
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, fSize }, 1.f });
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, fSize }, 1.f });
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, fSize }, 1.f });
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, fSize }, 1.f });
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, -fSize }, 1.f });
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, -fSize }, 1.f });
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, -fSize }, 1.f });
		gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, -fSize }, 1.f });


		GLclampf r = 0.f, g = 1.f, b = 0.f;
		for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
			gColor.push_back(glm::vec3{ r,g,b });
		}

		// Index
		gIndex.push_back(0);
		gIndex.push_back(1);
		gIndex.push_back(2);
		gIndex.push_back(2);
		gIndex.push_back(3);
		gIndex.push_back(0);

		gIndex.push_back(0);
		gIndex.push_back(4);
		gIndex.push_back(1);
		gIndex.push_back(1);
		gIndex.push_back(4);
		gIndex.push_back(5);

		gIndex.push_back(5);
		gIndex.push_back(4);
		gIndex.push_back(7);
		gIndex.push_back(7);
		gIndex.push_back(6);
		gIndex.push_back(5);

		gIndex.push_back(6);
		gIndex.push_back(7);
		gIndex.push_back(3);
		gIndex.push_back(2);
		gIndex.push_back(6);
		gIndex.push_back(3);
		//
		gIndex.push_back(1);
		gIndex.push_back(5);
		gIndex.push_back(6);
		gIndex.push_back(6);
		gIndex.push_back(2);
		gIndex.push_back(1);
		//
		gIndex.push_back(0);
		gIndex.push_back(3);
		gIndex.push_back(7);
		gIndex.push_back(7);
		gIndex.push_back(4);
		gIndex.push_back(0);
	}
};

class CObject {
protected:
	CModel* pModel;
	CShader* pShader;

	glm::vec3 vWorldPosition;
	glm::mat4 mat_Projection;
	CCamera& camera;

	vec3Buffer* pBuffer;
public:
	CObject(CCamera& cam, glm::vec3 vPos) : camera(cam) {
		vWorldPosition = vPos;
		mat_Projection = PROJ(60.f);
	}
	~CObject()
	{
		delete pModel;
		delete pShader;
		delete[] pBuffer;
	}
	void SetWorldPosition(glm::vec3 pos)
	{
		vWorldPosition = pos;
	}
	glm::vec3& GetWorldPosition()
	{
		return vWorldPosition;
	}
	virtual void Update()
	{
		glm::mat4 translate = glm::translate(vWorldPosition);
		pShader->Update(translate, camera.GetCameraProj(), mat_Projection, pBuffer);
	}
	vec3Buffer* GetBuffer()
	{
		return pBuffer;
	}
	void DrawObject()
	{
		pShader->DrawObject(pModel->GetIndex(), pModel->GetDrawType());
	}
	bool& IsDraw() { return pModel->GetIsDraw(); }
};


class CObject_CCube : public CObject {
protected:
public:
	CObject_CCube(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }) : CObject(cam, pos) {
		pModel = new CCube(size);

		pBuffer = new vec3Buffer[pModel->GetLayoutSize()];
		pBuffer[BUFFER_VERTEX] = pModel->GetVertex();
		pBuffer[BUFFER_COLOR] = pModel->GetColor();

		pShader = new CShader(pModel->GetLayoutSize(), pBuffer);
	}

	virtual void Update()
	{
		glm::mat4 translate = glm::translate(vWorldPosition);
		pShader->Update(translate, camera.GetCameraProj(), mat_Projection, pBuffer);
	}
};