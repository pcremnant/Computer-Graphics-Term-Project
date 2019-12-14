#pragma once
#include "CObject.h"

class CObject_Particle : public CObject {
protected:
	int int_Frame;
	std::pair<int, int> frameNumber;
	int int_Timer;
	//int int_ParticleType;
public:
	CObject_Particle(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	//virtual void GetKeyboard(unsigned int key) final {
	//	switch (key) {
	//	case 'w':
	//		vec3_WorldPosition.z -= 0.1;
	//		break;
	//	case 's':
	//		vec3_WorldPosition.z += 0.1;
	//		break;
	//	case 'a':
	//		vec3_WorldPosition.x -= 0.1;
	//		break;
	//	case 'd':
	//		vec3_WorldPosition.x += 0.1;
	//		break;
	//	case 'r':
	//		vec3_WorldPosition.y += 0.1;
	//		break;
	//	case 'f':
	//		vec3_WorldPosition.y -= 0.1;
	//		break;
	//	}
	//}
};