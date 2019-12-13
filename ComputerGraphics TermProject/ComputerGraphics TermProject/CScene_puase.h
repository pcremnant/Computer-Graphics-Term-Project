#pragma once
#include "CScene.h"

class CScene_pause : public CScene {
protected:
	glm::mat4 sceneProjection;
public:
	CScene_pause();
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeyboardInput(unsigned char key);
	virtual void GetMouseInput(int button, int state, int x, int y) final;
	virtual void GetMouseMotionInput(int x, int y) final;
};