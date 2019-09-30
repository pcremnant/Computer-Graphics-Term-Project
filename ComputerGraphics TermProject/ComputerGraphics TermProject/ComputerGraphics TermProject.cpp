// OpenGL_SET.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 프로젝트 속성 - 링커 - 명령줄에 glew32.lib freeglut.lib 추가

#include<GL/glew.h>
#include<GL/freeglut.h>
#include<gl/freeglut_ext.h>
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/matrix.hpp>
#include<glm/gtx/transform.hpp>

#include <iostream>
#include <random>

using namespace std;

#define POSITION_WINDOW_X 0					// 윈도우 창 x 위치
#define POSITION_WINDOW_Y 0					// 윈도우 창 y 위치
#define WIDTH_WINDOW 800					// 윈도우 창 너비
#define HEIGHT_WINDOW 600					// 윈도우 창 높이

GLclampf cColorWindow_Red = 1.0f;
GLclampf cColorWindow_Green = 1.0f;
GLclampf cColorWindow_Blue = 1.0f;

GLvoid drawScene(GLvoid);					// 콜백함수 : 그리기
GLvoid Reshape(int w, int h);				// 콜백함수 : 다시 그리기
GLvoid Keyboard(unsigned char key, int x, int y);		// 콜백함수 : 키보드 입력
GLvoid TimerFunction(int value);						// 콜백함수 : 타이머
GLvoid Mouse(int type, int state, int x, int y);		// 콜백함수 : 마우스


void main(int argc, char** argv) {									// 윈도우 출력하고 콜백함수 설정 --- 윈도우 생성하기

	glutInit(&argc, argv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// 디스플레이 모드 설정
	glutInitWindowPosition(POSITION_WINDOW_X, POSITION_WINDOW_Y);	// 윈도우의 위치 지정
	glutInitWindowSize(WIDTH_WINDOW, HEIGHT_WINDOW);				// 윈도우의 크기 지정
	glutCreateWindow("Example1");									// 윈도우 생성

	glewExperimental = GL_TRUE;										//--- GLEW 초기화하기
	if (glewInit() != GLEW_OK)										// glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene);										// 출력 함수의 지정
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);										// 키보드 콜백함수 등록
	glutTimerFunc(1000, TimerFunction, 1);							// 타이머 콜백함수 등록
	glutMainLoop();													// 이벤트 처리 시작 
}
GLvoid drawScene() {
	glClearColor(cColorWindow_Red, cColorWindow_Green, cColorWindow_Blue, 1.0f);							// 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT);									// 설정된 색으로 전체를 칠하기

																	// 그리기 부분 구현
																	//--- 그리기 관련 부분이 여기에 포함된다			
	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Reshape(int w, int h) {							// 콜백 함수: 다시 그리기
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)		// 키보드 콜백함수
{

}

GLvoid TimerFunction(int value)							// 타이머 콜백함수
{

}

GLvoid Mouse(int type, int state, int x, int y)			// 마우스 콜백함수
{

}
