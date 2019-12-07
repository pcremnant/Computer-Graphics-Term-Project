#include "CScene_main.h"

CScene_main::CScene_main() : CScene() {
	std::cout << "main scene create!" << std::endl;
	pObjectManager = new CObjectManager(camera);
	pObjectManager->AddObject(new CObject_cube(camera, glm::vec3{ 3,0.01,3 }, glm::vec3{ 0,-0.15,0 }));
}

void CScene_main::Update() {
	pObjectManager->Update();
}

void CScene_main::Draw() {
	pObjectManager->Draw();
}

void CScene_main::GetKeaboardInput(unsigned char key) {
	// 테스트용 코드!
	// 나중에 제대로 된 값으로 넣을 것
	switch (key) {
	case '5':
		pObjectManager->AddObject(new CObject_cube(camera, glm::vec3{ 3,0.01,3 }, glm::vec3{ 0,-0.15,0 }));
		break;
	case '6':
		if (pObjectManager->GetObjects().size() != 0)
			pObjectManager->DeleteObject(pObjectManager->GetObjects()[0]);
		break;
	case '1':
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_QUIT);
		break;
	case '2':
		next = SetNextScene(FRAMEWORK_ACTION_PUSH, SCENE_TYPE_MAIN);
		break;
	case '3':
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_NONE);
		break;
	case '4':
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