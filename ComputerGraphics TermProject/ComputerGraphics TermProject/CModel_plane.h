#pragma once
#include "CModel.h"

class CModel_plane : public CModel {
protected:
	float fSize;
public:
	CModel_plane(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 }, int horizontalRepeat = 1, int verticalRepeat = 1);
	virtual void SetFrame(int frame, std::pair<int, int> frameNumber) final {
		// u = frame % frameNumber.second
		int u = frame % frameNumber.second;
		int v = frameNumber.first - 1 - (frame / frameNumber.second);

		float ver = (float)1 / (float)frameNumber.second;
		float hor = (float)1 / (float)frameNumber.first;

		gUv[0] = (glm::vec3{ (u + 1) * ver,v * hor,0 });
		gUv[1] = (glm::vec3{ (u + 1) * ver,(v + 1) * hor,0 });
		gUv[2] = (glm::vec3{ u * ver, (v + 1) * hor,0 });
		gUv[3] = (glm::vec3{ u * ver, (v + 1) * hor,0 });
		gUv[4] = (glm::vec3{ u * ver,v * hor,0 });
		gUv[5] = (glm::vec3{ (u + 1) * ver,v * hor,0 });

		gUv[6] = (glm::vec3{ (u + 1) * ver,v * hor,0 });
		gUv[7] = (glm::vec3{ (u + 1) * ver,(v + 1) * hor,0 });
		gUv[8] = (glm::vec3{ u * ver, (v + 1) * hor,0 });
		gUv[9] = (glm::vec3{ u * ver, (v + 1) * hor,0 });
		gUv[10] = (glm::vec3{ u * ver,v * hor,0 });
		gUv[11] = (glm::vec3{ (u + 1) * ver,v * hor,0 });

		//gUv[0] = (glm::vec3{ 0.2,0,0 });
		//gUv[1] = (glm::vec3{ 0.2,0.2,0 });
		//gUv[2] = (glm::vec3{ 0, 0.2,0 });
		//gUv[3] = (glm::vec3{ 0, 0.2,0 });
		//gUv[4] = (glm::vec3{ 0,0,0 });
		//gUv[5] = (glm::vec3{ 0.2,0,0 });
	}
};