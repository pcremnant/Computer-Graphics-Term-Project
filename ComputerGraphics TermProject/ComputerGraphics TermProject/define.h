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
#define BUFFER_NORMAL 2
#define BUFFER_UV 3

#define LAYOUT_VERTEX 1
#define LAYOUT_COLOR 2
#define LAYOUT_NORMAL 3
#define LAYOUT_UV 4
#define LAYOUT_UI 5
#define LAYOUT_NUM 6

#define WINDOW_X 100							// 윈도우 창 x 위치
#define WINDOW_Y 100							// 윈도우 창 y 위치
#define WINDOW_WIDTH 800						// 윈도우 창 너비
#define WINDOW_HEIGHT 600						// 윈도우 창 높이

#define MAIN_SCENE_START 0
#define MAIN_SCENE_QUIT 1

#define PAUSE_SCENE_NONE 0
#define PAUSE_SCENE_RESUME 1
#define PAUSE_SCENE_QUIT 2


#define NONE_COLLISION_CHECK -1000

typedef std::vector<glm::vec4> vec4Buffer;
typedef std::vector<glm::vec3> vec3Buffer;
typedef std::vector<glm::vec2> vec2Buffer;

// 윈도우 배경색
extern GLclampf cBackground_red;
extern GLclampf cBackground_green;
extern GLclampf cBackground_blue;
extern int int_Score;
extern int int_HighScore;

// 투영 방식
#define PROJ(fovy) glm::perspective(glm::radians(fovy), (float)800 / (float)600, 0.1f, 100.0f)
#define ORTHO glm::ortho(-WINDOW_WIDTH/2.f, WINDOW_WIDTH/2.f, -WINDOW_HEIGHT/2.f, WINDOW_HEIGHT/2.f, 0.1f, 100.f)

// 색상 랜덤 설정
void SetRandomColor(GLclampf& r, GLclampf& g, GLclampf& b);

//배틀씬 
#define ZOOM_IN 40.f
#define ZOOM_OUT 70.f
#define ZOOM_SPEED 1.f

#define COLLISION_BULLET 1
#define COLLISION_ENEMY 2
#define COLLISION_FLOOR 3
#define COLLISION_BARRIGATE 4

#define MAPSIZE 10