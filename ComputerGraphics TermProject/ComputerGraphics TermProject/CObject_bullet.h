#pragma once
#include "CObject.h"

class CObject_bullet : public CObject {
protected:
	glm::vec3 vec3_Direction;
	float float_Speed;
public:
	CObject_bullet(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};