#include "CObject_EndPressanykey.h"
#include "CModel_plane.h"

CObject_EndPressanykey::CObject_EndPressanykey(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj), size(size) {
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_UI, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });


	SetBuffer();

	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;

	t.emplace_back("./resource/texture/end_pressanykey.bmp");
	sz.emplace_back(512, 512);

	AddTexture(0, t, sz);

	CreateShader();

	inBox = false;
	type = PAUSE_SCENE_NONE;
	clicked = false;
}

void CObject_EndPressanykey::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);

	}
}

void CObject_EndPressanykey::GetMouse(int button, int state, int x, int y) { }

void CObject_EndPressanykey::GetMouseMotion(int x, int y) {}

int CObject_EndPressanykey::GetState() { return -1; }
