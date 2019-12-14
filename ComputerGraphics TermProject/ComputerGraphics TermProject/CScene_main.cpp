#include "CScene_main.h"
#include "CObject_MainBackground.h"
#include "CObject_MainStartgame.h"
#include "CObject_MainQuitgame.h"

#include "CObject_particle.h"

CScene_main::CScene_main() : CScene() {
	std::cout << "main scene create!" << std::endl;
	sceneProjection =ORTHO;
	pObjectManager = new CObjectManager(camera);
	pObjectManager->AddObject(new CObject_MainBackground(camera, glm::vec3{ WINDOW_WIDTH/2,WINDOW_HEIGHT/2,0 }, glm::vec3{ 0,0,0 }, sceneProjection));
	pObjectManager->AddObject(new CObject_MainStartgame(camera, glm::vec3{ 100,40,0 }, glm::vec3{ -300,-100,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_MainQuitgame(camera, glm::vec3{ 100,40,0 }, glm::vec3{ -300,-200,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_Particle(camera, glm::vec3{ 40,40,0 }, glm::vec3{ 0,0,1 }, sceneProjection));
}

void CScene_main::Update() {
	pObjectManager->Update();
	int type = pObjectManager->GetState();
	switch (type) {
	case MAIN_SCENE_START:
		next = SetNextScene(FRAMEWORK_ACTION_PUSH, SCENE_TYPE_BATTLE);
		break;
	case MAIN_SCENE_QUIT:
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_QUIT);
		break;
	}
}

void CScene_main::Draw() {
	pObjectManager->Draw();
}

void CScene_main::GetKeyboardInput(unsigned char key) {
	// 테스트용 코드!
	// 나중에 제대로 된 값으로 넣을 것
	camera.Move(key);
	switch (key) {
	case '1':
		next = SetNextScene(FRAMEWORK_ACTION_PUSH, SCENE_TYPE_PAUSE);
		break;
	}
	pObjectManager->GetKeyboard(key);
}

void CScene_main::GetMouseInput(int button, int state, int x, int y) {
	pObjectManager->GetMouse(button, state, x, y);
}
void CScene_main::GetMouseMotionInput(int x, int y) {
	pObjectManager->GetMouseMotion(x, y);
}

void CScene_main::Enter() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene_main::Exit() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}