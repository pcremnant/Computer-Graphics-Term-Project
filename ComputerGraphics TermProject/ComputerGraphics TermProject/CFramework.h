#pragma once

#include "CScene_main.h"
#include <stack>

class CFramework {
private:
	std::stack<CScene*> stack_Scene;
public:
	CFramework() {
		stack_Scene.push(new CScene_main());
		stack_Scene.top()->Enter();
	}
	~CFramework() {
		while (!stack_Scene.size() <= 0)
			stack_Scene.pop();
	}
	void Update() {
		stack_Scene.top()->Update();
		std::pair<int, int> next = stack_Scene.top()->NextScene();
		switch (next.first) {
		case STAY_SCENE:
			break;
		case PUSH_SCENE:
			stack_Scene.top()->Exit();
			switch (next.second) {
			case SCENE_MAIN:
				stack_Scene.push(new CScene_main());
				break;
			}
			break;
			stack_Scene.top()->Enter();
		case POP_SCENE:
			stack_Scene.top()->Exit();
			switch (next.second) {
			case SCENE_NONE:
				stack_Scene.pop();
				break;
			case SCENE_QUIT:
				while (stack_Scene.size() > 0)
					stack_Scene.pop();
				PostQuitMessage(0);
				break;
			}
			if (stack_Scene.size() <= 0)
				PostQuitMessage(0);
			stack_Scene.top()->Enter();
			break;
		case CHANGE_SCENE:
			stack_Scene.top()->Exit();
			stack_Scene.pop();
			switch (next.second) {
			case SCENE_MAIN:
				stack_Scene.push(new CScene_main());
				break;
			}
			stack_Scene.top()->Enter();
			break;
		}
		if (stack_Scene.size() <= 0)
			PostQuitMessage(0);
	}
	void Draw() {
		stack_Scene.top()->Draw();
	}
	void GetKeaboardInput(unsigned char key) {
		stack_Scene.top()->GetKeaboardInput(key);
	}
	void GetMouseInput() {

	}
	virtual void GetMouseMotionInput() {

	}

};