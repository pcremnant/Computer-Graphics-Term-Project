#pragma once
#include "CModel.h"

class CModel_plane : public CModel {
protected:
	float fSize;
public:
	CModel_plane(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 }, int horizontalRepeat = 1, int verticalRepeat = 1);
};