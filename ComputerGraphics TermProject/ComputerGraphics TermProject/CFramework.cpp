#include "CFramework.h"

#include "CScene_main.h"
#include "CScene_puase.h"
#include "CScene_battle.h"

CFramework::CFramework() {
	stack_Scene.push(new CScene_main());
	stack_Scene.top()->Enter();
}

CFramework::~CFramework() {
	while (!stack_Scene.size() <= 0)
		stack_Scene.pop();
}

void CFramework::Update() {
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
			while (!stack_Scene.empty())
				stack_Scene.pop();
			stack_Scene.push(new CScene_battle());
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
			// ¹èÆ² ¾À Ãß°¡
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

void CFramework::Draw() {
	stack_Scene.top()->Draw();
}

void CFramework::GetKeyboardInput(unsigned char key) {
	stack_Scene.top()->GetKeyboardInput(key);
}

void CFramework::GetMouseInput(int button, int state, int x, int y) {
	stack_Scene.top()->GetMouseInput(button, state, x, y);
}

void CFramework::GetMouseMotionInput(int x, int y) {
	stack_Scene.top()->GetMouseMotionInput(x, y);
}
