#include "CScene.h"

CScene::CScene() {
	pObjectManager = new CObjectManager(camera);
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