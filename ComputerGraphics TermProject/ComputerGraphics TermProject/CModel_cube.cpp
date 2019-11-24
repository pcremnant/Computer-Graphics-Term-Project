#include "CModel_cube.h"

CModel_cube::CModel_cube(glm::vec3 size = glm::vec3{ 1,1,1 }) : CModel(GL_TRIANGLES) {
	fSize = 0.5;
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, fSize }, 1.f });
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, fSize }, 1.f });
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, fSize }, 1.f });
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, fSize }, 1.f });
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, -fSize }, 1.f });
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, -fSize }, 1.f });
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, -fSize }, 1.f });
	gVertex.push_back(glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, -fSize }, 1.f });


	GLclampf r = 0.f, g = 1.f, b = 0.f;


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.push_back(glm::vec3{ r,g,b });
	}

	// Index
	gIndex.push_back(0);
	gIndex.push_back(1);
	gIndex.push_back(2);
	gIndex.push_back(2);
	gIndex.push_back(3);
	gIndex.push_back(0);

	gIndex.push_back(0);
	gIndex.push_back(4);
	gIndex.push_back(1);
	gIndex.push_back(1);
	gIndex.push_back(4);
	gIndex.push_back(5);

	gIndex.push_back(5);
	gIndex.push_back(4);
	gIndex.push_back(7);
	gIndex.push_back(7);
	gIndex.push_back(6);
	gIndex.push_back(5);

	gIndex.push_back(6);
	gIndex.push_back(7);
	gIndex.push_back(3);
	gIndex.push_back(2);
	gIndex.push_back(6);
	gIndex.push_back(3);
	//
	gIndex.push_back(1);
	gIndex.push_back(5);
	gIndex.push_back(6);
	gIndex.push_back(6);
	gIndex.push_back(2);
	gIndex.push_back(1);
	//
	gIndex.push_back(0);
	gIndex.push_back(3);
	gIndex.push_back(7);
	gIndex.push_back(7);
	gIndex.push_back(4);
	gIndex.push_back(0);
}