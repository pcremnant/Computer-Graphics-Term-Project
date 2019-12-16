#include "CScene_end.h"
#include "CObject_EndBackground.h"
#include "CObject_EndGameover.h"
#include "CObject_EndPressanykey.h"
#include "CObject_EndScore.h"

CScene_end::CScene_end() : CScene() {
	std::cout << "main scene create!" << std::endl;
	sceneProjection = ORTHO;
	pObjectManager = new CObjectManager(camera);
	pObjectManager->AddObject(new CObject_EndBackground(camera, glm::vec3{ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2,0 }, glm::vec3{ 0,0,0 }, sceneProjection));
	pObjectManager->AddObject(new CObject_EndGameover(camera, glm::vec3{ 250,150,0 }, glm::vec3{ 0,150,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_EndPressanykey(camera, glm::vec3{ 300,100,0 }, glm::vec3{ 0,-150,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_EndScore(camera, glm::vec3{ 200,100,0 }, glm::vec3{ -150,0,1 }, sceneProjection));
	// 여기에 High Score 추가하기
	if (int_HighScore < int_Score)
		int_HighScore = int_Score;
	ptrDrawNum = std::make_unique<Draw_Number>(camera, "resource/texture/numsest.png");
}


void CScene_end::Update() {
	pObjectManager->Update();
	int type = pObjectManager->GetState();
	switch (type) {
	case PAUSE_SCENE_QUIT:
		next = SetNextScene(FRAMEWORK_ACTION_CHANGE, SCENE_TYPE_MAIN);
		break;
	case PAUSE_SCENE_RESUME:
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_NONE);
		break;
	default:
		break;
	}
}

void CScene_end::Draw() {
	pObjectManager->Draw();
	//---숫자 그리기
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	ptrDrawNum->drawStart();
	ptrDrawNum->drawInt(int_HighScore, 0, 0.22, 0.2, 0, 1, 1);
	ptrDrawNum->drawInt(int_Score, 0, -0.03, 0.2, 1, 1, 1);
	ptrDrawNum->drawEnd();
}

void CScene_end::GetKeyboardInput(unsigned char key) {
	switch (key) {
	default:
		next = SetNextScene(FRAMEWORK_ACTION_CHANGE, SCENE_TYPE_MAIN);
		break;
	}
	pObjectManager->GetKeyboard(key);
}

void CScene_end::GetMouseInput(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			next = SetNextScene(FRAMEWORK_ACTION_CHANGE, SCENE_TYPE_MAIN);
		}
	}
	pObjectManager->GetMouse(button, state, x, y);
}
void CScene_end::GetMouseMotionInput(int x, int y) {
	pObjectManager->GetMouseMotion(x, y);
}

void CScene_end::Enter() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene_end::Exit() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}