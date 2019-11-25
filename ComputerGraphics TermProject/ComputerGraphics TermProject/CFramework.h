#pragma once

#include "CScene_main.h"


class CFramework {
private:
	CScene* pScene;
public:
	CFramework() {
		pScene = new CScene_main();
	}
	void Update() {
		pScene->Update();
	}
	void Draw() {
		pScene->Draw();
	}
	void GetKeaboardInput(unsigned char key) {
		pScene->GetKeaboardInput(key);
	}
	void GetMouseInput() {

	}
	virtual void GetMouseMotionInput() {

	}

};