#pragma once
#include "CModel.h"

class CModel_cube : public CModel {
protected:
	float fSize;
public:
	CModel_cube(glm::vec3 size);
};