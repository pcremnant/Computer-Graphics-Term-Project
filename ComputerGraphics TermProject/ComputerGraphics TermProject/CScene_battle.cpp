#include "CScene_battle.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"//https://github.com/nothings/stb/blob/master/stb_image.h

CScene_battle::CScene_battle() : CScene() {
	std::cout << "battle scene create!" << std::endl;
	int_Count = 0;
	isZoom = false;
	float_ZoomSize = 70.f;
	sceneProjection = PROJ(70.f);
	//pObjectManager = new CObjectManager(camera);
	oObjectManager = new CObjectManager(camera);
	MakeFloor();
	MakeBarrigate();
	oObjectManager->AddObject(new CObject_aim(camera, glm::vec3{ 1,1,1 }, glm::vec3{ 0,6,0 }, ORTHO));

	ptrDrawNum = std::make_unique<DrawNumObject>(camera, "resource/texture/numsest.png");
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

void CScene_battle::Draw() {
	pObjectManager->Draw();
	oObjectManager->Draw();

	//---숫자 그리기
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	ptrDrawNum->drawStart();
	if (object_Barrigate.size() > 1) {
		ptrDrawNum->drawInt(object_Barrigate[0]->GetHp(), 0.7, 0.9, 0.1, 0, 1, 0);
		ptrDrawNum->drawInt(object_Barrigate[1]->GetHp(), 0.7, 0.75, 0.1, 0, 1, 0);
	}
	else if (object_Barrigate.size() != 0) {
		ptrDrawNum->drawInt(0, 0.7, 0.9, 0.1, 0, 1, 0);
		ptrDrawNum->drawInt(object_Barrigate[0]->GetHp(), 0.7, 0.75, 0.1, 0, 1, 0);
	}
	else {
		ptrDrawNum->drawInt(0, 0.7, 0.9, 0.1, 0, 1, 0);
		ptrDrawNum->drawInt(0, 0.7, 0.75, 0.1, 0, 1, 0);
	}
	ptrDrawNum->drawEnd();

}

void CScene_battle::GetKeyboardInput(unsigned char key) {
	switch (key) {
	case 27:
		next = SetNextScene(FRAMEWORK_ACTION_PUSH, SCENE_TYPE_PAUSE);
		break;
	}
	camera.Move(key);
	pObjectManager->GetKeyboard(key);
	oObjectManager->GetKeyboard(key);
}

void CScene_battle::GetSpecialKeyboardInput(int key) {
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

void CScene_battle::Spawn() {
	std::random_device rnd;
	std::mt19937 rn(rnd());
	std::uniform_int<> distribution(0, 10);
	int xpos = distribution(rn) - 5;
	CObject_enemy* new_Enemy = new CObject_enemy(camera, glm::vec3{ 0.1,0.1,0.1 }, glm::vec3{ xpos,0, -MAPSIZE - 5 }, sceneProjection);
	object_Enemy.push_back(new_Enemy);
	pObjectManager->AddObject(new_Enemy);
}

void CScene_battle::CheckCollision() {
	pObjectManager->CheckCollision(object_Bullet, object_Enemy);
	pObjectManager->CheckCollision(object_Bullet, object_Floor);
	pObjectManager->CheckCollision(object_Bullet, object_Barrigate);
	pObjectManager->CheckCollision(object_Enemy, object_Barrigate);
}

void CScene_battle::CheckDelete() {
	DeleteObject(object_Bullet);
	DeleteObject(object_Enemy);
	DeleteObject(object_Barrigate);
}

void CScene_battle::DeleteObject(std::vector<CObject*> &objects) {
	for (auto &iter : objects) {
		if (iter->IsDelete()) {
			pObjectManager->DeleteObject(iter);
			//delete iter;
			iter = nullptr;
		}
	}
	objects.erase(std::remove(begin(objects), end(objects), nullptr), end(objects));
}

void CScene_battle::MakeFloor() {
	CObject_DownFloor* dn_Floor = new CObject_DownFloor(camera, glm::vec3{ MAPSIZE,0,MAPSIZE }, glm::vec3{ 0,0,-5 }, sceneProjection);
	object_Floor.push_back(dn_Floor);
	pObjectManager->AddObject(dn_Floor);
	CObject_UpFloor* up_Floor = new CObject_UpFloor(camera, glm::vec3{ MAPSIZE,0,MAPSIZE }, glm::vec3{ 0,MAPSIZE * 2,-5 }, sceneProjection);
	object_Floor.push_back(up_Floor);
	pObjectManager->AddObject(up_Floor);
	CObject_LeftFloor* lf_Floor = new CObject_LeftFloor(camera, glm::vec3{ 0,MAPSIZE,MAPSIZE }, glm::vec3{ -MAPSIZE,MAPSIZE,-5 }, sceneProjection);
	object_Floor.push_back(lf_Floor);
	pObjectManager->AddObject(lf_Floor);
	CObject_RightFloor* rt_Floor = new CObject_RightFloor(camera, glm::vec3{ 0,MAPSIZE,MAPSIZE }, glm::vec3{ MAPSIZE,MAPSIZE,-5 }, sceneProjection);
	object_Floor.push_back(rt_Floor);
	pObjectManager->AddObject(rt_Floor);
	CObject_FrontFloor* ft_Floor = new CObject_FrontFloor(camera, glm::vec3{ MAPSIZE,MAPSIZE,0 }, glm::vec3{ 0,MAPSIZE,MAPSIZE - 5 }, sceneProjection);
	object_Floor.push_back(ft_Floor);
	pObjectManager->AddObject(ft_Floor);
	CObject_BackFloor* bk_Floor = new CObject_BackFloor(camera, glm::vec3{ MAPSIZE,MAPSIZE,0 }, glm::vec3{ 0,MAPSIZE,-MAPSIZE - 5 }, sceneProjection);
	object_Floor.push_back(bk_Floor);
	pObjectManager->AddObject(bk_Floor);
}

void CScene_battle::MakeBarrigate() {
	CObject_cube* first_Barrigate = new CObject_cube(camera, glm::vec3{ 10,1,0.3 }, glm::vec3{ 0,0,-5 }, sceneProjection);
	object_Barrigate.push_back(first_Barrigate);
	pObjectManager->AddObject(first_Barrigate);
	CObject_cube* second_Barrigate = new CObject_cube(camera, glm::vec3{ 10,5,0.5 }, glm::vec3{ 0,0,4 }, sceneProjection);
	object_Barrigate.push_back(second_Barrigate);
	pObjectManager->AddObject(second_Barrigate);
}

DrawNumObject::DrawNumObject(CCamera &camera, const char *imgStr)
{
	uiNumShader = std::make_unique<CShader>(LAYOUT_NUM, camera, 0);
	auto pid = uiNumShader->get_glShaderProgramID();

	initTexture(imgStr, texID);

	charID = glGetUniformLocation(pid, "uiCharid"); //--- lightPos 값전달
	infoID = glGetUniformLocation(pid, "offset"); //--- lightPos 값전달
	posID = glGetUniformLocation(pid, "pos"); //--- lightPos 값전달
	colorID = glGetUniformLocation(pid, "color"); //--- lightPos 값전달
}

void DrawNumObject::initTexture(const char * imgStr, GLuint & textureID)
{

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	unsigned char *data = stbi_load(imgStr, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Succeed texture" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

int DrawNumObject::drawIntpice(int num, int offset, float scale)
{
	int nextval = num / 10;
	int id = num % 10;

	if (nextval)
		offset = drawIntpice(num / 10, offset, scale);

	static int asdf{ 0 };
	glUniform1i(charID, id);
	glUniform3f(infoID, offset, scale, WINDOW_HEIGHT *1.f / WINDOW_WIDTH);

	glDrawArrays(GL_QUADS, 0, 4);
	offset++;

	return offset;
}

void DrawNumObject::drawInt(int num, float posx, float posy, float scale, float colorx, float colory, float colorz)
{
	glUniform2f(posID, posx, posy);
	glUniform3f(colorID, colorx, colory, colorz);
	drawIntpice(num, 0, scale);
}

void DrawNumObject::drawStart()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	uiNumShader->UseProgram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void DrawNumObject::drawEnd()
{
	glDisable(GL_BLEND);
}
