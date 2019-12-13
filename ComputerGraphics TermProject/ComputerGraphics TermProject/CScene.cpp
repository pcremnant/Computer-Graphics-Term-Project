#include "CScene.h"

CScene::CScene() {
	pObjectManager = new CObjectManager(camera);
	next = std::make_pair(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene::GetKeyboardInput(unsigned char key) {
	pObjectManager->GetKeyboard(key);
}
void CScene::GetMouseInput(int button, int state, int x, int y) {

}
void CScene::GetMouseMotionInput(int x, int y) {

}

std::pair<int, int> CScene::NextScene() {
	return next;
}

std::pair<int, int> CScene::SetNextScene(int FrameworkAction, int SceneType){
	return std::make_pair(FrameworkAction, SceneType);
}

