#include "CScene.h"

CScene::CScene() {
	pObjectManager = new CObjectManager(camera);
	next = std::make_pair(STAY_SCENE, SCENE_NONE);
}
void CScene::Update() {
	pObjectManager->Update();
}
void CScene::Draw() {
	pObjectManager->Draw();
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

std::pair<int, int> CScene::SetNextScene(int NextAction, int NextScene){
	return std::make_pair(NextAction, NextScene);
}

void CScene::Enter() {

}
void CScene::Exit() {

}