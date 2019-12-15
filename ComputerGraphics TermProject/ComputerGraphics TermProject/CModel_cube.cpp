#include "CModel_cube.h"

CModel_cube::CModel_cube(int layout, glm::vec3 size, glm::vec3 color, int horizontalRepeat, int verticalRepeat) : CModel(GL_TRIANGLES, layout, horizontalRepeat, verticalRepeat) {
	fSize = 1;
	glm::vec3 vertex[8] = {
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, -fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, -fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, -fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, -fSize }, 1.f }
	};
	// front
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[0]);
	// right
	gVertex.emplace_back(vertex[4]);
	gVertex.emplace_back(vertex[5]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[4]);
	// back
	gVertex.emplace_back(vertex[7]);
	gVertex.emplace_back(vertex[6]);
	gVertex.emplace_back(vertex[5]);
	gVertex.emplace_back(vertex[5]);
	gVertex.emplace_back(vertex[4]);
	gVertex.emplace_back(vertex[7]);
	// left
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[6]);
	gVertex.emplace_back(vertex[6]);
	gVertex.emplace_back(vertex[7]);
	gVertex.emplace_back(vertex[3]);
	// top
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[5]);
	gVertex.emplace_back(vertex[6]);
	gVertex.emplace_back(vertex[6]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[1]);
	// bottom
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[7]);
	gVertex.emplace_back(vertex[4]);
	gVertex.emplace_back(vertex[4]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[3]);


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}

	for (int i = 0; i < gVertex.size(); ++i) {
		if (i < 6) {
			gNormal.emplace_back(glm::vec3{ 0,0,1 });
		}
		else if (i < 12) {
			gNormal.emplace_back(glm::vec3{ 1,0,0 });
		}
		else if (i < 18) {
			gNormal.emplace_back(glm::vec3{ 0,0,-1 });
		}
		else if (i < 24) {
			gNormal.emplace_back(glm::vec3{ -1,0,0 });
		}
		else if (i < 30) {
			gNormal.emplace_back(glm::vec3{ 0,1,0 });
		}
		else if (i < 36) {
			gNormal.emplace_back(glm::vec3{ 0,-1,0 });
		}
	}

	for (int i = 0; i < gVertex.size(); ++i)
		gIndex.emplace_back(i);


	for (int i = 0; i < 6; ++i) {
		gUv.emplace_back(glm::vec3{ nVerticalRepeat,0,0 });
		gUv.emplace_back(glm::vec3{ nVerticalRepeat,nHoriziontalRepeat,0 });
		gUv.emplace_back(glm::vec3{ 0,nHoriziontalRepeat,0 });
		gUv.emplace_back(glm::vec3{ 0,nHoriziontalRepeat,0 });
		gUv.emplace_back(glm::vec3{ 0,0,0 });
		gUv.emplace_back(glm::vec3{ nVerticalRepeat,0,0 });
	}
}