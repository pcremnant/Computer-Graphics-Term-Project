#pragma once
#include "CScene.h"

class CScene_main : public CScene {
protected:
	glm::mat4 sceneProjection;
public:
	CScene_main();
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeaboardInput(unsigned char key);
	virtual void GetMouseInput(int button, int state, int x, int y) final;
	virtual void GetMouseMotionInput(int x, int y) final;
};