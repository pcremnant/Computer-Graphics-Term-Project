#pragma once
#include "CScene.h"
#include "UI_Particle.h"

class CScene_main : public CScene {
protected:
	glm::mat4 sceneProjection;
	int int_Timer;
public:
	CScene_main();
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeyboardInput(unsigned char key);
	virtual void GetMouseInput(int button, int state, int x, int y) final;
	virtual void GetMouseMotionInput(int x, int y) final;
};