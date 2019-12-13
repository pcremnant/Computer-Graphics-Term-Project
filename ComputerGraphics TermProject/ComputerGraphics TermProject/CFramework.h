#pragma once

#include <stack>
#include "CScene_main.h"
#include "CScene_puase.h"

//#include "CScene_battle.h"

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
		case FRAMEWORK_ACTION_STAY:
			break;

		case FRAMEWORK_ACTION_PUSH:
			stack_Scene.top()->Exit();
			switch (next.second) {
			case SCENE_TYPE_MAIN:
				while (!stack_Scene.empty())
					stack_Scene.pop();
				stack_Scene.push(new CScene_main());
				break;
			case SCENE_TYPE_BATTLE:
				//while (!stack_Scene.empty())
				//	stack_Scene.pop();
				// 배틀 씬 넣어주기
				//stack_Scene.push(new CScene_battle());
				break;
			case SCENE_TYPE_PAUSE:
				stack_Scene.push(new CScene_pause());
				break;
			}
			stack_Scene.top()->Enter();

		case FRAMEWORK_ACTION_POP:
			stack_Scene.top()->Exit();
			switch (next.second) {
			case SCENE_TYPE_NONE:
				stack_Scene.pop();
				break;
			case SCENE_TYPE_QUIT:
				while (stack_Scene.size() > 0)
					stack_Scene.pop();
				PostQuitMessage(0);
				break;
			default:
				break;
			}
			if (stack_Scene.size() <= 0)
				PostQuitMessage(0);
			stack_Scene.top()->Enter();
			break;

		case FRAMEWORK_ACTION_CHANGE:
			stack_Scene.top()->Exit();
			stack_Scene.pop();
			switch (next.second) {
			case SCENE_TYPE_MAIN:
				stack_Scene.push(new CScene_main());
				break;
			case SCENE_TYPE_BATTLE:
				// 배틀 씬 추가
				break;
			case SCENE_TYPE_PAUSE:
				stack_Scene.push(new CScene_pause());
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
	void GetKeyboardInput(unsigned char key) {
		stack_Scene.top()->GetKeyboardInput(key);
	}
	void GetMouseInput(int button, int state, int x, int y) {
		stack_Scene.top()->GetMouseInput(button, state, x, y);
	}
	void GetMouseMotionInput(int x, int y) {
		stack_Scene.top()->GetMouseMotionInput(x, y);
	}

};