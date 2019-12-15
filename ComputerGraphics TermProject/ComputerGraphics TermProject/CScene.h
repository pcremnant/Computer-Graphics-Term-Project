#pragma once
#include "CObjectManager.h"
#include "CCamera.h"


#define FRAMEWORK_ACTION_STAY -1
#define FRAMEWORK_ACTION_PUSH 0
#define FRAMEWORK_ACTION_CHANGE 1
#define FRAMEWORK_ACTION_POP 2

#define SCENE_TYPE_QUIT -2
#define SCENE_TYPE_NONE -1
#define SCENE_TYPE_MAIN 0
#define SCENE_TYPE_BATTLE 1
#define SCENE_TYPE_PAUSE 2
#define SCENE_TYPE_HELP 3



class CScene {
protected:
	CCamera camera;
	CObjectManager* pObjectManager;
	std::pair<int, int> next;
public:
	CScene();
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void GetSpecialKeyboardInput(int key) {};
	virtual void GetKeyboardInput(unsigned char key);
	virtual void GetMouseInput(int button, int state, int x, int y);
	virtual void GetMouseMotionInput(int x, int y);
	std::pair<int, int> SetNextScene(int FrameworkAction, int SceneType);
	std::pair<int, int> NextScene();
};