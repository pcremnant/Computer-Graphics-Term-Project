#include "CScene_main.h"

CScene_main::CScene_main() {
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
		next = SetNextScene(POP_SCENE, SCENE_QUIT);
		break;
	case 'p':
	case 'P':
		next = SetNextScene(PUSH_SCENE, SCENE_MAIN);
		break;
	case 'o':
	case 'O':
		next = SetNextScene(POP_SCENE, SCENE_NONE);
		break;
	case 'c':
	case 'C':
		next = SetNextScene(CHANGE_SCENE, SCENE_MAIN);
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
	next = SetNextScene(STAY_SCENE, SCENE_NONE);
}

void CScene_main::Exit() {
	next = SetNextScene(STAY_SCENE, SCENE_NONE);
}