#pragma once
#include "CObjectManager.h"
#include "CCamera.h"

class CScene {
protected:
	CCamera camera;
	CObjectManager* pObjectManager;
public:
	CScene();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeaboardInput(unsigned char key);
	virtual void GetMouseInput();
	virtual void GetMouseMotionInput();
};