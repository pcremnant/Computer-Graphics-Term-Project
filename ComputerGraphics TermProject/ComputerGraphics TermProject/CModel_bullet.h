#pragma once
#include "CModel.h"

class CModel_bullet : public CModel {
protected:
	float fSize;
public:
	CModel_bullet(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 });
};