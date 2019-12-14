#pragma once
#include "CScene.h"
#include "CObject_enemy.h"
#include "CObject_floor.h"
#include "CObject_bullet.h"
#include "CObject_aim.h"

class CScene_battle : public CScene {
protected:
	CObjectManager* oObjectManager;
	glm::mat4 sceneProjection;
	int int_Count;
	bool isZoom;
	float float_ZoomSize;
	std::vector<CObject*> object_Bullet;
	std::vector<CObject*> object_Enemy;
	std::vector<CObject*> object_Floor;
public:
	CScene_battle();
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeyboardInput(unsigned char key);
	virtual void GetMouseInput(int button, int state, int x, int y) final;
	virtual void GetMouseMotionInput(int x, int y) final;
	void Spawn();
	void CheckCollision();
	void CheckDelete();
	void MakeFloor();
};