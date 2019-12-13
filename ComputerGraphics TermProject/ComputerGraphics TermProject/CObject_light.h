#pragma once
#include "CObject.h"

class CObject_light : public CObject {
protected:
	float fLightPower;
	bool bLightOn;
public:
	CObject_light(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::vec3 color = glm::vec3{ 1,1,1 }, float power = 1000.f, glm::mat4 proj = glm::mat4{ 1.0, });
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f) final;
	virtual void GetKeyboard(unsigned int key) final;
	float GetLightPower() const;
};