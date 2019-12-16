#pragma once
#include<fstream>
#include<iterator>
#include "CScene.h"
//#include <memory>
#define BULLET_NUM_MAX 4



class CScene_battle : public CScene {
protected:
	glm::mat4 sceneProjection;
	short bullet_num;
	int int_Count;
	bool isZoom;
	float float_ZoomSize;
	std::vector<CObject*> object_Bullet;
	std::vector<CObject*> object_Enemy;
	std::vector<CObject*> object_Floor;
	std::vector<CObject*> object_Barrigate;
	std::vector<CObject*> object_Light;
	std::vector<CObject*> object_Obstacle;

	CObjectManager* oObjectManager;
	CObjectManager* pParticleObjectManager;
	CObjectManager* pLightObjectManager;

	int int_Timer;
	int int_StopTimer;
	bool bool_Night;

	std::unique_ptr< Draw_Number > ptrDrawNum;
	std::vector<glm::vec3> vector_ParticlePosition;
public:
	CScene_battle();
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeyboardInput(unsigned char key);
	virtual void GetMouseInput(int button, int state, int x, int y) final;
	virtual void GetMouseMotionInput(int x, int y) final;
	virtual void GetSpecialKeyboardInput(int key);
	void Spawn();
	void CheckCollision();
	void CheckDelete();
	void MakeFloor();
	void MakeBarrigate();
	void DeleteObject(std::vector<CObject*> &objects);
};