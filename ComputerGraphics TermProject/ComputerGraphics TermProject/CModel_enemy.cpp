#include "CModel_enemy.h"

CModel_enemy::CModel_enemy(int layout, glm::vec3 size, glm::vec3 color) : CModel(GL_TRIANGLES, layout) {
	SetObjectVertex("./resource/obj/devil.obj");
	for (auto &iter : gVertex) {
		iter = glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4(iter, 1.0);
	}
	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}
}
