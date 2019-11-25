#include "CObject.h"

CObject::CObject(CCamera& cam, glm::vec3 vPos) : camera(cam) {
	vWorldPosition = vPos;
	mat_Projection = PROJ(60.f);
}
CObject::~CObject()
{

}
void CObject::SetWorldPosition(glm::vec3 pos)
{
	vWorldPosition = pos;
}
glm::vec3 CObject::GetWorldPosition()
{
	return vWorldPosition;
}
void CObject::Update()
{

	for (int i = 0; i < vModel.size(); ++i) {
		glm::mat4 translate = glm::translate(vModelPosition[i]);
		vShader[i]->Update(translate, camera.GetCameraProj(), mat_Projection, vBuffer[i]);
	}
}
vec3Buffer* CObject::GetBuffer(int i)
{
	return vBuffer[i];
}
void CObject::DrawObject()
{
	for (int i = 0; i < vModel.size(); ++i) {
		vShader[i]->DrawObject(vModel[i]->GetIndex(), vModel[i]->GetDrawType());
	}
}
bool& CObject::IsDraw(int i) { return vModel[i]->GetIsDraw(); }