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

#define BUFFER_VERTEX 0							// pBuffer�� ���ؽ� �ε���
#define BUFFER_COLOR 1
#define BUFFER_NORMAL 2
#define BUFFER_UV 3

#define WINDOW_X 100							// ������ â x ��ġ
#define WINDOW_Y 100							// ������ â y ��ġ
#define WINDOW_WIDTH 800						// ������ â �ʺ�
#define WINDOW_HEIGHT 600						// ������ â ����

typedef std::vector<glm::vec4> vec4Buffer;
typedef std::vector<glm::vec3> vec3Buffer;
typedef std::vector<glm::vec2> vec2Buffer;

// ������ ����
extern GLclampf cBackground_red;
extern GLclampf cBackground_green;
extern GLclampf cBackground_blue;

// ���� ���
#define PROJ(fovy) glm::perspective(glm::radians(fovy), (float)800 / (float)600, 0.1f, 100.0f)
#define ORTHO glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.1f, 100.f)

// ���� ���� ����
void SetRandomColor(GLclampf& r, GLclampf& g, GLclampf& b);
