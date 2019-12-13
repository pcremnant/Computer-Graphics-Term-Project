#include "CModel_plane.h"

CModel_plane::CModel_plane(int layout, glm::vec3 size, glm::vec3 color, int horizontalRepeat, int verticalRepeat) : CModel(GL_TRIANGLES, layout, horizontalRepeat, verticalRepeat) {
	fSize = 1;
	glm::vec3 vertex[8] = {
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, 0 }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, 0 }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, 0 }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, 0 }, 1.f },
	};

	// front
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[0]);


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}

	gNormal.emplace_back(glm::vec3{ 0,0,1 });
	gNormal.emplace_back(glm::vec3{ 0,0,1 });
	gNormal.emplace_back(glm::vec3{ 0,0,1 });
	gNormal.emplace_back(glm::vec3{ 0,0,1 });
	gNormal.emplace_back(glm::vec3{ 0,0,1 });
	gNormal.emplace_back(glm::vec3{ 0,0,1 });


	for (int i = 0; i < gVertex.size(); ++i)
		gIndex.emplace_back(i);


	gUv.emplace_back(glm::vec3{ nVerticalRepeat,0,0 });
	gUv.emplace_back(glm::vec3{ nVerticalRepeat,nHoriziontalRepeat,0 });
	gUv.emplace_back(glm::vec3{ 0,nHoriziontalRepeat,0 });
	gUv.emplace_back(glm::vec3{ 0,nHoriziontalRepeat,0 });
	gUv.emplace_back(glm::vec3{ 0,0,0 });
	gUv.emplace_back(glm::vec3{ nVerticalRepeat,0,0 });
}