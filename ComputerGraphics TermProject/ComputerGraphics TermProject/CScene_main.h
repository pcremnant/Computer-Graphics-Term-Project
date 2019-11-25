#pragma once
#include "CScene.h"

class CScene_main : public CScene {
protected:
public:
	CScene_main();
	virtual void Update();
	virtual void Draw();
	virtual void GetKeaboardInput(unsigned char key);
	virtual void GetMouseInput();
	virtual void GetMouseMotionInput();
};