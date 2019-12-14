#pragma once
#include "CObject.h"

class CObject_aim : public CObject {
protected:
	glm::mat4 mat4_WorldRotate;
	float RotateAngleX;
	float RotateAngleY;
public:
	CObject_aim(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = ORTHO);
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual void GetKeyboard(unsigned int key);
};