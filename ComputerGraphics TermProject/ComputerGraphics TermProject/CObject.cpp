#include "CObject.h"

void CObject::SetBuffer() {
	for (int i = 0; i < vector_Model.size(); ++i) {
		int layout = vector_Model[i]->GetLayoutSize();
		vector_Buffer.emplace_back(new std::vector<glm::vec3>[layout]);
		vector_Buffer[i][BUFFER_VERTEX] = vector_Model[i]->GetVertex();
		vector_Buffer[i][BUFFER_COLOR] = vector_Model[i]->GetColor();
		if (layout >= 4) {
			vector_Buffer[i][BUFFER_NORMAL] = vector_Model[i]->GetNormal();
			vector_Buffer[i][BUFFER_UV] = vector_Model[i]->GetUv();
		}
		else if (layout >= 3) {
			vector_Buffer[i][BUFFER_NORMAL] = vector_Model[i]->GetNormal();
		}
	}
}

void CObject::CreateShader() {
	for (int i = 0; i < vector_Model.size(); ++i) {
		std::vector<const char*> s;
		for (auto iter : textures) {
			if (iter.first == i)
				s = std::move(iter.second);
		}

		if (s.size() > 0)
			vector_Shader.emplace_back(std::make_unique<CShader>(vector_Model[i]->GetLayoutSize(), camera, mat_Projection, vector_Buffer[i].get(), s));
		else
			vector_Shader.emplace_back(std::make_unique<CShader>(vector_Model[i]->GetLayoutSize(), camera, mat_Projection, vector_Buffer[i].get()));
	}
}

void CObject::ClearTexture() {
	textures.clear();
}

void CObject::AddTexture(int modelIndex, std::vector<const char*> textureName) {
	textures.emplace_back(std::make_pair(modelIndex, textureName));
}

CObject::CObject(CCamera& cam, glm::vec3 vPos) : camera(cam) {
	bool_Delete = false;
	vec3_WorldPosition = vPos;
	mat_Projection = PROJ(60.f);
}
CObject::~CObject() { }

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
void CObject::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}
std::vector<glm::vec3>* CObject::GetBuffer(int i)
{
	return vector_Buffer[i].get();
}
void CObject::DrawObject()
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		vector_Shader[i]->DrawObject(vector_Model[i]->GetIndex(), vector_Model[i]->GetDrawType());
	}
}
bool& CObject::IsDelete() { return bool_Delete; }