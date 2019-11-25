#pragma once
#include "CObjectManager.h"
#include "CCamera.h"

#define STAY_SCENE -1
#define PUSH_SCENE 0
#define CHANGE_SCENE 1
#define POP_SCENE 2

#define SCENE_QUIT -2
#define SCENE_NONE -1
#define SCENE_MAIN 0


class CScene {
protected:
	CCamera camera;
	CObjectManager* pObjectManager;
	std::pair<int, int> next;
public:
	CScene();
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeaboardInput(unsigned char key);
	virtual void GetMouseInput();
	virtual void GetMouseMotionInput();
	std::pair<int, int> SetNextScene(int NextAction, int NextScene);
	std::pair<int, int> NextScene();
};