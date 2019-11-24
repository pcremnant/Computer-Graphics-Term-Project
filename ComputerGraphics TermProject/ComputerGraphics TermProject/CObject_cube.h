#pragma once
#include "CObject.h"

class CObject_cube : public CObject {
protected:
public:
	CObject_cube(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 });
	virtual void Update();
};