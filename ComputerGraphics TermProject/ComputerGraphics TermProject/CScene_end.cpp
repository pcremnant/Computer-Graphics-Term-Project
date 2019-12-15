#include "CScene_end.h"
#include "CObject_EndBackground.h"
#include "CObject_EndGameover.h"
#include "CObject_EndPressanykey.h"

CScene_end::CScene_end() : CScene() {
	std::cout << "main scene create!" << std::endl;
	sceneProjection = ORTHO;
	pObjectManager = new CObjectManager(camera);
	pObjectManager->AddObject(new CObject_EndBackground(camera, glm::vec3{ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2,0 }, glm::vec3{ 0,0,0 }, sceneProjection));
	pObjectManager->AddObject(new CObject_EndGameover(camera, glm::vec3{ 250,80,0 }, glm::vec3{ 0,150,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_EndPressanykey(camera, glm::vec3{ 100,40,0 }, glm::vec3{ 0,-50,1 }, sceneProjection));
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
}

void CScene_end::GetKeyboardInput(unsigned char key) {
	switch (key) {
	case '1':
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_NONE);
		break;
	}
	pObjectManager->GetKeyboard(key);
}

void CScene_end::GetMouseInput(int button, int state, int x, int y) {
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