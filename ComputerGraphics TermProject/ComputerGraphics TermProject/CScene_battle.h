#pragma once
#include<fstream>
#include<iterator>
#include "CScene.h"
#include "CObject_enemy.h"
#include "CObject_floor.h"
#include "CObject_bullet.h"
#include "CObject_aim.h"
#include "CObject_cube.h"
//#include <memory>
#define BULLET_NUM_MAX 4

class DrawNumObject
{
	std::unique_ptr<CShader> uiNumShader;

	GLuint texID;

	GLint charID;
	GLint infoID;
	GLint posID;
	GLint colorID;

public:
	DrawNumObject(CCamera&, const char *imgStr);

	void initTexture(const char *imgStr, GLuint& textureID);

	void drawStart();
	void drawInt(int num, float posx, float posy, float scale, float colorx = 1, float colory = 1, float colorz = 1);
	void drawEnd();
private:
	int drawIntpice(int num, int offset, float scale);
};


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
	CObjectManager* oObjectManager;
	CObjectManager* pParticleObjectManager;


	std::unique_ptr< DrawNumObject > ptrDrawNum;
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