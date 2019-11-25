#pragma once
#include "CModel.h"
#include "CShader.h"
#include "CCamera.h"

class CObject {
protected:
	std::vector<CModel*> vModel;
	std::vector<CShader*> vShader;

	std::vector<glm::vec3> vModelPosition;
	glm::vec3 vWorldPosition;
	glm::mat4 mat_Projection;
	CCamera& camera;

	std::vector<vec3Buffer*> vBuffer;
public:
	CObject(CCamera& cam, glm::vec3 vPos);
	~CObject();
	void SetWorldPosition(glm::vec3 pos);
	glm::vec3 GetWorldPosition();
	virtual void Update();
	vec3Buffer* GetBuffer(int i = 0);
	void DrawObject();
	bool& IsDraw(int i = 0);
};
