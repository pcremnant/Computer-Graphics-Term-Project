#include "CObject.h"

CObject::CObject(CCamera& cam, glm::vec3 vPos) : camera(cam) {
	vWorldPosition = vPos;
	mat_Projection = PROJ(60.f);
}
CObject::~CObject()
{
	delete pModel;
	delete pShader;
	delete[] pBuffer;
}
void CObject::SetWorldPosition(glm::vec3 pos)
{
	vWorldPosition = pos;
}
glm::vec3& CObject::GetWorldPosition()
{
	return vWorldPosition;
}
void CObject::Update()
{
	glm::mat4 translate = glm::translate(vWorldPosition);
	pShader->Update(translate, camera.GetCameraProj(), mat_Projection, pBuffer);
}
vec3Buffer* CObject::GetBuffer()
{
	return pBuffer;
}
void CObject::DrawObject()
{
	pShader->DrawObject(pModel->GetIndex(), pModel->GetDrawType());
}
bool& CObject::IsDraw() { return pModel->GetIsDraw(); }