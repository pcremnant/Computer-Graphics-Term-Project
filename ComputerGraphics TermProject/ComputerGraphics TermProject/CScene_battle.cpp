#include "CScene_battle.h"


CScene_battle::CScene_battle() : CScene() {
	std::cout << "battle scene create!" << std::endl;
	int_Count = 0;
	isZoom = false;
	float_ZoomSize = 70.f;
	sceneProjection = PROJ(70.f);
	oObjectManager = new CObjectManager(camera);
	MakeFloor();
	pObjectManager->AddObject(new CObject_aim(camera, glm::vec3{1,1,1}, glm::vec3{0,4,1}, ORTHO));
}

void CScene_battle::Update() {
	if (isZoom) {
		if (float_ZoomSize > ZOOM_IN)	
			float_ZoomSize -= ZOOM_SPEED;
		pObjectManager->ChangeFov(PROJ(float_ZoomSize));
	}
	else {
		if (float_ZoomSize < ZOOM_OUT)
			float_ZoomSize += ZOOM_SPEED;
		pObjectManager->ChangeFov(PROJ(float_ZoomSize));
	}
	pObjectManager->Update(glm::vec3{ 0,0,5 });
	oObjectManager->Update(glm::vec3{ 0,0,5 });

	CheckCollision();
	CheckDelete();

	if (int_Count % 100 == 0) //적 스폰 빈도
		Spawn();
		
	int type = pObjectManager->GetState();
	switch (type) {
	case MAIN_SCENE_START:
		break;
	case MAIN_SCENE_QUIT:
		next = SetNextScene(FRAMEWORK_ACTION_POP, SCENE_TYPE_QUIT);
		break;
	}
	int_Count++;
}

void CScene_battle ::Draw() {
	pObjectManager->Draw();
	oObjectManager->Draw();
}

void CScene_battle::GetKeyboardInput(unsigned char key) {
	// 테스트용 코드!
	// 나중에 제대로 된 값으로 넣을 것
	switch (key) {
	case '5':
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
	oObjectManager->GetKeyboard(key);
}

void CScene_battle::GetMouseInput(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			isZoom = !isZoom;
		}
	}
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			CObject_bullet* new_Bullet = new CObject_bullet(camera, glm::vec3{ 0.1,0.1,0.1 }, camera.GetEye(), sceneProjection);
			object_Bullet.push_back(new_Bullet);
			pObjectManager->AddObject(new_Bullet);
		}
	}
	pObjectManager->GetMouse(button, state, x, y);
}
void CScene_battle::GetMouseMotionInput(int x, int y) {
	pObjectManager->GetMouseMotion(x, y);
}

void CScene_battle::Enter() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene_battle::Exit() {
	next = SetNextScene(FRAMEWORK_ACTION_STAY, SCENE_TYPE_NONE);
}

void CScene_battle::Spawn(){ 
	std::random_device rnd;
	std::mt19937 rn(rnd());
	std::uniform_int<> distribution(0, 10);
	int xpos = distribution(rn) - 5;
	CObject_enemy* new_Enemy = new CObject_enemy(camera, glm::vec3{ 0.1,0.1,0.1 }, glm::vec3{ xpos,0, -MAPSIZE-5 }, sceneProjection);
	object_Enemy.push_back(new_Enemy);
	pObjectManager->AddObject(new_Enemy);
}

void CScene_battle::CheckCollision() {
	pObjectManager->CheckCollision(object_Bullet, object_Enemy);
	pObjectManager->CheckCollision(object_Bullet, object_Floor);
}

void CScene_battle::CheckDelete() {
	for (auto &iter : object_Bullet) {
		if (iter->IsDelete()) {
			pObjectManager->DeleteObject(iter);
			delete iter;
			iter = nullptr;
		}
	}
	object_Bullet.erase(std::remove(begin(object_Bullet), end(object_Bullet), nullptr), end(object_Bullet));

	for (auto &iter : object_Enemy) {
		if (iter->IsDelete()) {
			pObjectManager->DeleteObject(iter);
			delete iter;
			iter = nullptr;
		}
	}
	object_Enemy.erase(std::remove(begin(object_Enemy), end(object_Enemy), nullptr), end(object_Enemy));
}

void CScene_battle::MakeFloor() {
	CObject_DownFloor* dn_Floor = new CObject_DownFloor(camera, glm::vec3{ MAPSIZE,0,MAPSIZE }, glm::vec3{ 0,0,-5 }, sceneProjection);
	object_Floor.push_back(dn_Floor);
	pObjectManager->AddObject(dn_Floor);
	CObject_UpFloor* up_Floor = new CObject_UpFloor(camera, glm::vec3{ MAPSIZE,0,MAPSIZE }, glm::vec3{ 0,MAPSIZE * 2,-5 }, sceneProjection);
	object_Floor.push_back(up_Floor);
	pObjectManager->AddObject(up_Floor);
	CObject_LeftFloor* lf_Floor = new CObject_LeftFloor(camera, glm::vec3{ 0,MAPSIZE,MAPSIZE }, glm::vec3{ -MAPSIZE,MAPSIZE,- 5 }, sceneProjection);
	object_Floor.push_back(lf_Floor);
	pObjectManager->AddObject(lf_Floor);
	CObject_RightFloor* rt_Floor = new CObject_RightFloor(camera, glm::vec3{ 0,MAPSIZE,MAPSIZE }, glm::vec3{ MAPSIZE,MAPSIZE,- 5 }, sceneProjection);
	object_Floor.push_back(rt_Floor);
	pObjectManager->AddObject(rt_Floor);
	CObject_FrontFloor* ft_Floor = new CObject_FrontFloor(camera, glm::vec3{ MAPSIZE,MAPSIZE,0 }, glm::vec3{ 0,MAPSIZE,MAPSIZE - 5 }, sceneProjection);
	object_Floor.push_back(ft_Floor);
	pObjectManager->AddObject(ft_Floor);
	CObject_BackFloor* bk_Floor = new CObject_BackFloor(camera, glm::vec3{ MAPSIZE,MAPSIZE,0 }, glm::vec3{ 0,MAPSIZE,-MAPSIZE - 5 }, sceneProjection);
	object_Floor.push_back(bk_Floor);
	pObjectManager->AddObject(bk_Floor);
}