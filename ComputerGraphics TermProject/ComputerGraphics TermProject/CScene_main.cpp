#include "CScene_main.h"

CScene_main::CScene_main() : CScene() {
	pObjectManager = new CObjectManager(camera);
}
void CScene_main::Update() {
	pObjectManager->Update();
}
void CScene_main::Draw() {
	pObjectManager->Draw();
}
void CScene_main::GetKeaboardInput(unsigned char key) {
	switch (key) {
	case 'q':
	case 'Q':
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_QUIT);
		break;
	case 'p':
	case 'P':
		next = SetNextScene(FRAMEWORK_ACTION_PUSH, SCENE_TYPE_MAIN);
		break;
	case 'o':
	case 'O':
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_NONE);
		break;
	case 'c':
	case 'C':
		next = SetNextScene(FRAMEWORK_ACTION_CHANGE, SCENE_TYPE_MAIN);
		break;
	}
	camera.Move(key);
	pObjectManager->GetKeyboard(key);
}
void CScene_main::GetMouseInput() {

}
void CScene_main::GetMouseMotionInput() {

}

void CScene_main::Enter() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene_main::Exit() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}