#pragma once
#include "CObject.h"

class CObject_enemy : public CObject {
protected:
	glm::vec3 vec3_Direction;
	float float_Speed;
	short changeDirecton;
	short short_Hp;
	bool isColObstacle;
	short short_count = 0;
public:
	CObject_enemy(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 },glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual void Update(std::vector<glm::vec3> lightPos = std::vector<glm::vec3>(), std::vector<glm::vec3> lightColor = std::vector<glm::vec3>(), std::vector<float> lightPower = std::vector<float>());
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};