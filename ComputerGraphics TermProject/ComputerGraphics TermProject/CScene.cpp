#include "CScene.h"

CScene::CScene() {
	pObjectManager = new CObjectManager(camera);
	next = std::make_pair(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene::GetKeaboardInput(unsigned char key) {
	pObjectManager->GetKeyboard(key);
}
void CScene::GetMouseInput() {

}
void CScene::GetMouseMotionInput() {

}

std::pair<int, int> CScene::NextScene() {
	return next;
}

std::pair<int, int> CScene::SetNextScene(int FrameworkAction, int SceneType){
	return std::make_pair(FrameworkAction, SceneType);
}
