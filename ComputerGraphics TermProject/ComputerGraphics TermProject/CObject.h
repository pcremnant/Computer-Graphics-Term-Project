#pragma once
#include "CModel.h"
#include "CShader.h"
#include "CCamera.h"

class CObject {
protected:
	std::vector<CModel*> vector_Model;
	std::vector<CShader*> vector_Shader;

	std::vector<glm::vec3> vector_ModelPosition;
	glm::vec3 vec3_WorldPosition;
	glm::mat4 mat_Projection;
	CCamera& camera;

	std::vector<vec3Buffer*> vector_Buffer;
public:
	CObject(CCamera& cam, glm::vec3 vPos);
	~CObject();
	void SetWorldPosition(glm::vec3 pos);
	glm::vec3 GetWorldPosition();
	virtual void GetKeyboard(unsigned int key);
	virtual void Update();
	vec3Buffer* GetBuffer(int i = 0);
	void DrawObject();
	bool& IsDraw(int i = 0);
};
