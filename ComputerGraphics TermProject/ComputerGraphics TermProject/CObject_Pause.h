#pragma once
#include "CObject.h"

class CObject_Pause : public CObject {
protected:
	glm::vec3 size;
	bool inBox;
	int type;
	bool clicked;
public:
	CObject_Pause(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f) final;
	virtual void GetMouse(int button, int state, int x, int y) final;
	virtual void GetMouseMotion(int x, int y) final;
	virtual int GetState() final;
};