#include "CScene_puase.h"
#include "CObject_Pause.h"
#include "CObject_PauseBackground.h"
#include "CObject_PauseResumegame.h"
#include "CObject_PauseQuitgame.h"

CScene_pause::CScene_pause() : CScene() {
	std::cout << "main scene create!" << std::endl;
	sceneProjection = ORTHO;
	pObjectManager = new CObjectManager(camera);
	pObjectManager->AddObject(new CObject_PauseBackground(camera, glm::vec3{ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2,0 }, glm::vec3{ 0,0,0 }, sceneProjection));
	pObjectManager->AddObject(new CObject_Pause(camera, glm::vec3{ 250,80,0 }, glm::vec3{ 0,150,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_PauseResumegame(camera, glm::vec3{ 100,40,0 }, glm::vec3{ 0,-50,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_PauseQuitgame(camera, glm::vec3{ 100,40,0 }, glm::vec3{ 0,-150,1 }, sceneProjection));
}

void CScene_pause::Update() {
	pObjectManager->Update();
	int type = pObjectManager->GetState();
	switch (type) {
	case PAUSE_SCENE_QUIT:
		next = SetNextScene(FRAMEWORK_ACTION_CHANGE, SCENE_TYPE_MAIN);
		break;
	case PAUSE_SCENE_RESUME:
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_NONE);
		// = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_BATTLE);
		break;
	default:
		break;
	}
}

void CScene_pause::Draw() {
	pObjectManager->Draw();
}

void CScene_pause::GetKeyboardInput(unsigned char key) {
	switch (key) {
	case '1':
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_NONE);
		break;
	}
	pObjectManager->GetKeyboard(key);
}

void CScene_pause::GetMouseInput(int button, int state, int x, int y) {
	pObjectManager->GetMouse(button, state, x, y);
}
void CScene_pause::GetMouseMotionInput(int x, int y) {
	pObjectManager->GetMouseMotion(x, y);
}

void CScene_pause::Enter() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene_pause::Exit() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}