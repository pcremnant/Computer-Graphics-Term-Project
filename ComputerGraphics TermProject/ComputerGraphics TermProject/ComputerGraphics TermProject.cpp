// OpenGL_SET.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 프로젝트 속성 - 링커 - 명령줄에 glew32.lib freeglut.lib 추가
// 프로젝트 속성 - C/C++ - 전처리기에 _CRT_SECURE_NO_WARNINGS 추가

#include "CFramework.h"

CFramework* pFramework;

using namespace std;


GLvoid drawScene(GLvoid);								// 콜백함수 : 그리기
GLvoid Reshape(int w, int h);							// 콜백함수 : 다시 그리기
GLvoid Keyboard(unsigned char key, int x, int y);		// 콜백함수 : 키보드 입력
GLvoid TimerFunction(int value);						// 콜백함수 : 타이머
GLvoid Mouse(int type, int state, int x, int y);// 콜백함수 : 마우스
GLvoid MouseMotion(int x, int y) {};
GLvoid MousePassiveMotion(int x, int y);

//GLvoid SpecialKeyboad(int key, int x, int y);

void main(int argc, char** argv) {									// 윈도우 출력하고 콜백함수 설정 --- 윈도우 생성하기

	glutInit(&argc, argv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);					// 디스플레이 모드 설정
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);	// 윈도우의 위치 지정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);				// 윈도우의 크기 지정
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
	// ----------
	pFramework = new CFramework();


	// ---------- OpenGL 설정 초기화 ----------

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutDisplayFunc(drawScene);										// 출력 함수의 지정
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);										// 키보드 콜백함수 등록
	glutTimerFunc(1, TimerFunction, 1);								// 타이머 콜백함수 등록
	glutMainLoop();													// 이벤트 처리 시작 

}

GLvoid drawScene() {
	glClearColor(cBackground_red, cBackground_green, cBackground_blue, 1.0f);							// 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);									// 설정된 색으로 전체를 칠하기
	pFramework->Draw();
	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Reshape(int w, int h) {							// 콜백 함수: 다시 그리기
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)		// 키보드 콜백함수
{
	pFramework->GetKeyboardInput(key);
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)							// 타이머 콜백함수
{
	pFramework->Update();
	glutPostRedisplay();
	glutTimerFunc(40, TimerFunction, 1);
}

GLvoid Mouse(int button, int state, int x, int y)			// 마우스 콜백함수
{
	pFramework->GetMouseInput(button, state, x, y);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {


		float fX = ((float)x - (float)WINDOW_WIDTH / 2.f) * 2.f / (float)WINDOW_WIDTH;
		float fY = (-1.f) * ((float)y - (float)WINDOW_HEIGHT / 2.f) * 2.f / (float)WINDOW_HEIGHT;


	}
}

GLvoid MousePassiveMotion(int x, int y)
{
	pFramework->GetMouseMotionInput(x,y);
}