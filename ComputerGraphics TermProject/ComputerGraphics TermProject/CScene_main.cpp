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
	pObjectManager->AddObject(new CObject_MainStartgame(camera, glm::vec3{ 100,40,0 }, glm::vec3{ 270,-100,1 }, sceneProjection));
	pObjectManager->AddObject(new CObject_MainQuitgame(camera, glm::vec3{ 100,40,0 }, glm::vec3{ 270,-200,1 }, sceneProjection));
	int_Timer = 0;
	int_Score = 0;
}

void CScene_main::Update() {
	//if (dynamic_cast<CObject_MainStartgame*>(pObjectManager->GetObjects()[1])->GetInBox()) {
	//	int_Timer++;
	//	if (int_Timer >= 15) {
	//		std::random_device rnd;
	//		std::mt19937 rn(rnd());
	//		std::uniform_int_distribution<int> rangeX(-100, 100);
	//		std::uniform_int_distribution<int> rangeY(-40, 40);
	//		glm::vec3 pos = pObjectManager->GetObjects()[1]->GetWorldPosition() + glm::vec3{ rangeX(rn),rangeY(rn),1 };
	//		pObjectManager->AddObject(UI_Particle::CreateParticle(PARTICLE_EXPLOSION_1, camera, glm::vec3{ 40,40,0 }, pos, sceneProjection));
	//		int_Timer = 0;
	//	}
	//}


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
	//camera.Move(key);
	switch (key) {
	case '1':
		next = SetNextScene(FRAMEWORK_ACTION_PUSH, SCENE_TYPE_PAUSE);
		break;
	}
	pObjectManager->GetKeyboard(key);
}

void CScene_main::GetMouseInput(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			int worldX = x - WINDOW_WIDTH / 2;
			int worldY = WINDOW_HEIGHT / 2 - y;
			pObjectManager->AddObject(UI_Particle::CreateParticle(PARTICLE_EXPLOSION_1, camera, glm::vec3{ 40,40,0 }, glm::vec3{ worldX,worldY,1 }, sceneProjection));
		}
	}
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