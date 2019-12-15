#pragma once
#include "CObject.h"
//#pragma comment(lib, "winmm")
//#include <mmsystem.h>

class CObject_bullet : public CObject {
protected:
	//Fmod_snd sound;
	glm::vec3 vec3_Direction;
	float float_Speed;
	float gravity_Speed;
public:
	CObject_bullet(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual void Update(std::vector<glm::vec3> lightPos = std::vector<glm::vec3>(), std::vector<glm::vec3> lightColor = std::vector<glm::vec3>(), std::vector<float> lightPower = std::vector<float>());
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};