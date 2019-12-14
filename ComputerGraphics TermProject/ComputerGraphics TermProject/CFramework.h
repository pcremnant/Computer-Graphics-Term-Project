#pragma once

#include <stack>

#include "CScene_main.h"
#include "CScene_puase.h"
//#include "CScene_battle.h"

class CFramework {
private:
	std::stack<CScene*> stack_Scene;
public:
	CFramework();
	~CFramework();
	void Update();
	void Draw();
	void GetKeyboardInput(unsigned char key);
	void GetMouseInput(int button, int state, int x, int y);
	void GetMouseMotionInput(int x, int y);

};