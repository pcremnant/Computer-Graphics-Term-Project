#include "CObject_Bullet_UI.h"
#include "CModel_plane.h"

CObject_Bullet_UI::CObject_Bullet_UI(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_UI, glm::vec3{ 0.2,0.1, 0 }, glm::vec3(1, 0, 0)));


	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });

	SetBuffer();
	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;

	t.emplace_back("./resource/texture/BULLET_UI.bmp");
	sz.emplace_back(408, 158);

	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_Bullet_UI::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{

	for (int i = 0; i < vector_Model.size(); ++i) {
		vector_Shader[i]->Update(glm::vec3{ 1,1,1 }, glm::vec3{ 0.7,-0.9,0 }, vector_Buffer[i].get());
	}
}

