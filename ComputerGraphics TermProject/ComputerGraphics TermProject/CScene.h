#pragma once
#include "CObjectManager.h"
#include "CCamera.h"


#define FRAMEWORK_ACTION_STAY -1
#define FRAMEWORK_ACTION_PUSH 0
#define FRAMEWORK_ACTION_CHANGE 1
#define FRAMEWORK_ACTION_POP 2

#define SCENE_TYPE_QUIT -2
#define SCENE_TYPE_NONE -1
#define SCENE_TYPE_MAIN 0
#define SCENE_TYPE_BATTLE 1
#define SCENE_TYPE_PAUSE 2
#define SCENE_TYPE_END 3



class CScene {
protected:
	CCamera camera;
	CObjectManager* pObjectManager;
	std::pair<int, int> next;
public:
	CScene();
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void GetSpecialKeyboardInput(int key) {};
	virtual void GetKeyboardInput(unsigned char key);
	virtual void GetMouseInput(int button, int state, int x, int y);
	virtual void GetMouseMotionInput(int x, int y);
	std::pair<int, int> SetNextScene(int FrameworkAction, int SceneType);
	std::pair<int, int> NextScene();
};

class Draw_Number
{
	std::unique_ptr<CShader> Shader_Num_UI;
	GLuint texID;
	GLint charID;
	GLint infoID;
	GLint posID;
	GLint colorID;

public:
	Draw_Number(CCamera&, const char *imgName);
	void initTexture(const char *imgStr, GLuint& textureID);
	void drawStart();
	void drawInt(int num, float posx, float posy, float scale, float colorx = 1, float colory = 1, float colorz = 1);
	void drawEnd();
private:
	int drawIntpice(int num, int offset, float scale);
};
