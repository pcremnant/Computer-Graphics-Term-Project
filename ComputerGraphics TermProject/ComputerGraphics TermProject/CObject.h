#pragma once
#include "CModel.h"
#include "CShader.h"
#include "CCamera.h"

class CObject {
protected:
	CModel* pModel;
	CShader* pShader;

	glm::vec3 vWorldPosition;
	glm::mat4 mat_Projection;
	CCamera& camera;

	vec3Buffer* pBuffer;
public:
	CObject(CCamera& cam, glm::vec3 vPos);
	~CObject();
	void SetWorldPosition(glm::vec3 pos);
	glm::vec3& GetWorldPosition();
	virtual void Update();
	vec3Buffer* GetBuffer();
	void DrawObject();
	bool& IsDraw();
};
