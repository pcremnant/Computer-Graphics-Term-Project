#pragma once
#include "CModel.h"
#include "CShader.h"

class CObject {
protected:
	CModel* pModel;
	CShader* pShader;

	glm::vec3 vWorldPosition;
	glm::mat4 mat_Projection;
	CCamera& camera;

	vec3Buffer* pBuffer;
public:
	CObject(CCamera& cam, glm::vec3 vPos) : camera(cam) {
		vWorldPosition = vPos;
		mat_Projection = PROJ(60.f);
	}
	~CObject()
	{
		delete pModel;
		delete pShader;
		delete[] pBuffer;
	}
	void SetWorldPosition(glm::vec3 pos)
	{
		vWorldPosition = pos;
	}
	glm::vec3& GetWorldPosition()
	{
		return vWorldPosition;
	}
	virtual void Update()
	{
		glm::mat4 translate = glm::translate(vWorldPosition);
		pShader->Update(translate, camera.GetCameraProj(), mat_Projection, pBuffer);
	}
	vec3Buffer* GetBuffer()
	{
		return pBuffer;
	}
	void DrawObject()
	{
		pShader->DrawObject(pModel->GetIndex(), pModel->GetDrawType());
	}
	bool& IsDraw() { return pModel->GetIsDraw(); }
};


class CObject_CCube : public CObject {
protected:
public:
	CObject_CCube(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }) : CObject(cam, pos) {
		pModel = new CCube(size);

		pBuffer = new vec3Buffer[pModel->GetLayoutSize()];
		pBuffer[BUFFER_VERTEX] = pModel->GetVertex();
		pBuffer[BUFFER_COLOR] = pModel->GetColor();

		pShader = new CShader(pModel->GetLayoutSize(), pBuffer);
	}

	virtual void Update()
	{
		glm::mat4 translate = glm::translate(vWorldPosition);
		pShader->Update(translate, camera.GetCameraProj(), mat_Projection, pBuffer);
	}
};