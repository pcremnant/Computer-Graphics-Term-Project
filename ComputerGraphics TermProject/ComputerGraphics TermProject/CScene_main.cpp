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
	camera.Move(key);
	pObjectManager->GetKeyboard(key);
}
void CScene_main::GetMouseInput() {

}
void CScene_main::GetMouseMotionInput() {

}