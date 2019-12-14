#include "UI_Particle.h"

//UI_Particle() {}

CObject* UI_Particle::CreateParticle(int effect, CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) {
	switch (effect) {
	case PARTICLE_EXPLOSION_1:
		return new CObject_Particle(cam, size, pos, proj);
	}
}
