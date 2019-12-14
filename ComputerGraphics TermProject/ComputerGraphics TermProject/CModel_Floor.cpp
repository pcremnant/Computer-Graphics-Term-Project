#include "CModel_floor.h"

CModel_DownFloor::CModel_DownFloor(int layout, glm::vec3 size, glm::vec3 color) : CModel(GL_TRIANGLES, layout) {
	fSize = 1;
	glm::vec3 vertex[4] = {
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize, 0, -fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize, 0 ,fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize, 0 ,fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize, 0 ,-fSize}, 1.f }
	};

	// front
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[1]);


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}

	gNormal.emplace_back(glm::vec3{ 0,1,0 });
	gNormal.emplace_back(glm::vec3{ 0,1,0 });
	gNormal.emplace_back(glm::vec3{ 0,1,0 });
	gNormal.emplace_back(glm::vec3{ 0,1,0 });
	gNormal.emplace_back(glm::vec3{ 0,1,0 });
	gNormal.emplace_back(glm::vec3{ 0,1,0 });


	for (int i = 0; i < gVertex.size(); ++i)
		gIndex.emplace_back(i);


	gUv.emplace_back(glm::vec3{ 1,0,0 });
	gUv.emplace_back(glm::vec3{ 1,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,0,0 });
	gUv.emplace_back(glm::vec3{ 1,0,0 });
}

CModel_LeftFloor::CModel_LeftFloor(int layout, glm::vec3 size, glm::vec3 color) : CModel(GL_TRIANGLES, layout) {
	fSize = 1;
	glm::vec3 vertex[4] = {
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, fSize, -fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, fSize ,fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, -fSize ,fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, -fSize,-fSize }, 1.f }
	};																

	// front
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[3]);


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}

	gNormal.emplace_back(glm::vec3{ 1,0,0 });
	gNormal.emplace_back(glm::vec3{ 1,0,0 });
	gNormal.emplace_back(glm::vec3{ 1,0,0 });
	gNormal.emplace_back(glm::vec3{ 1,0,0 });
	gNormal.emplace_back(glm::vec3{ 1,0,0 });
	gNormal.emplace_back(glm::vec3{ 1,0,0 });


	for (int i = 0; i < gVertex.size(); ++i)
		gIndex.emplace_back(i);


	gUv.emplace_back(glm::vec3{ 1,0,0 });
	gUv.emplace_back(glm::vec3{ 1,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,0,0 });
	gUv.emplace_back(glm::vec3{ 1,0,0 });
}

CModel_RightFloor::CModel_RightFloor(int layout, glm::vec3 size, glm::vec3 color) : CModel(GL_TRIANGLES, layout) {
	fSize = 1;
	glm::vec3 vertex[4] = {
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, fSize, -fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, fSize ,fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, -fSize ,fSize }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ 0, -fSize,-fSize }, 1.f }
	};

	// front
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[2]);


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}

	gNormal.emplace_back(glm::vec3{ -1,0,0 });
	gNormal.emplace_back(glm::vec3{ -1,0,0 });
	gNormal.emplace_back(glm::vec3{ -1,0,0 });
	gNormal.emplace_back(glm::vec3{ -1,0,0 });
	gNormal.emplace_back(glm::vec3{ -1,0,0 });
	gNormal.emplace_back(glm::vec3{ -1,0,0 });


	for (int i = 0; i < gVertex.size(); ++i)
		gIndex.emplace_back(i);


	gUv.emplace_back(glm::vec3{ 1,0,0 });
	gUv.emplace_back(glm::vec3{ 1,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,0,0 });
	gUv.emplace_back(glm::vec3{ 1,0,0 });
}

CModel_BackFloor::CModel_BackFloor(int layout, glm::vec3 size, glm::vec3 color) : CModel(GL_TRIANGLES, layout) {
	fSize = 1;
	glm::vec3 vertex[4] = {
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, 0 }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, 0 }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, 0 }, 1.f },
		glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, 0 }, 1.f }
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


	gUv.emplace_back(glm::vec3{ 1,0,0 });
	gUv.emplace_back(glm::vec3{ 1,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,0,0 });
	gUv.emplace_back(glm::vec3{ 1,0,0 });
}

CModel_UpFloor::CModel_UpFloor(int layout, glm::vec3 size, glm::vec3 color) : CModel(GL_TRIANGLES, layout) {
	fSize = 1;
	glm::vec3 vertex[4] = {
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize, 0, -fSize }, 1.f },
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize, 0 ,fSize }, 1.f },
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize, 0 ,fSize }, 1.f },
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize, 0 ,-fSize}, 1.f }
	};

	// bot
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[2]);


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}

	gNormal.emplace_back(glm::vec3{ 0,-1,0 });
	gNormal.emplace_back(glm::vec3{ 0,-1,0 });
	gNormal.emplace_back(glm::vec3{ 0,-1,0 });
	gNormal.emplace_back(glm::vec3{ 0,-1,0 });
	gNormal.emplace_back(glm::vec3{ 0,-1,0 });
	gNormal.emplace_back(glm::vec3{ 0,-1,0 });


	for (int i = 0; i < gVertex.size(); ++i)
		gIndex.emplace_back(i);


	gUv.emplace_back(glm::vec3{ 1,0,0 });
	gUv.emplace_back(glm::vec3{ 1,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,0,0 });
	gUv.emplace_back(glm::vec3{ 1,0,0 });
}

CModel_FrontFloor::CModel_FrontFloor(int layout, glm::vec3 size, glm::vec3 color) : CModel(GL_TRIANGLES, layout) {
	fSize = 1;
	glm::vec3 vertex[4] = {
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,-fSize, 0 }, 1.f },
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ fSize,fSize, 0 }, 1.f },
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,fSize, 0 }, 1.f },
			glm::scale(glm::mat4{ 1.f, }, size) * glm::vec4{ glm::vec3{ -fSize,-fSize, 0 }, 1.f }
	};

	// bot
	gVertex.emplace_back(vertex[3]);
	gVertex.emplace_back(vertex[2]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[1]);
	gVertex.emplace_back(vertex[0]);
	gVertex.emplace_back(vertex[3]);


	for (auto iter = gVertex.begin(); iter != gVertex.end(); ++iter) {
		gColor.emplace_back(color);
	}

	gNormal.emplace_back(glm::vec3{ 0,0,-1 });
	gNormal.emplace_back(glm::vec3{ 0,0,-1 });
	gNormal.emplace_back(glm::vec3{ 0,0,-1 });
	gNormal.emplace_back(glm::vec3{ 0,0,-1 });
	gNormal.emplace_back(glm::vec3{ 0,0,-1 });
	gNormal.emplace_back(glm::vec3{ 0,0,-1 });


	for (int i = 0; i < gVertex.size(); ++i)
		gIndex.emplace_back(i);


	gUv.emplace_back(glm::vec3{ 1,0,0 });
	gUv.emplace_back(glm::vec3{ 1,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,1,0 });
	gUv.emplace_back(glm::vec3{ 0,0,0 });
	gUv.emplace_back(glm::vec3{ 1,0,0 });
}