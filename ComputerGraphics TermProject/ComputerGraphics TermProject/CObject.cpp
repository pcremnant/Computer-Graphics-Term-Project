#include "CObject.h"

CObject::CObject(CCamera& cam, glm::vec3 vPos) : camera(cam) {
	vec3_WorldPosition = vPos;
	mat_Projection = PROJ(60.f);
}
CObject::~CObject()
{

}
void CObject::SetWorldPosition(glm::vec3 pos)
{
	vec3_WorldPosition = pos;
}
void CObject::GetKeyboard(unsigned int key)
{

}
glm::vec3 CObject::GetWorldPosition()
{
	return vec3_WorldPosition;
}
void CObject::Update()
{

	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, camera.GetCameraProj(), mat_Projection, vector_Buffer[i]);
	}
}
vec3Buffer* CObject::GetBuffer(int i)
{
	return vector_Buffer[i];
}
void CObject::DrawObject()
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		vector_Shader[i]->DrawObject(vector_Model[i]->GetIndex(), vector_Model[i]->GetDrawType());
	}
}
bool& CObject::IsDraw(int i) { return vector_Model[i]->GetIsDraw(); }