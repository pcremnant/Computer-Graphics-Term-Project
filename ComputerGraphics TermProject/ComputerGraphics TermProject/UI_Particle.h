#pragma once
#include "CObject_particle.h"
// ��ƼŬ ������

#define PARTICLE_EXPLOSION_1 0

static class UI_Particle{
private:
public:
	//UI_Particle() {}
	static CObject* CreateParticle(int effect, CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj);
};