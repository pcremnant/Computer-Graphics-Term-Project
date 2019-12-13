#include "CObject_PauseQuitgame.h"
#include "CModel_plane.h"

CObject_PauseQuitgame::CObject_PauseQuitgame(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj), size(size) {
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_UI, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });


	SetBuffer();

	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;

	t.emplace_back("./resource/texture/pause_quit.bmp");
	sz.emplace_back(256, 256);

	AddTexture(0, t, sz);

	CreateShader();

	inBox = false;
	type = PAUSE_SCENE_QUIT;
	clicked = false;
}

void CObject_PauseQuitgame::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		glm::mat4 scale = glm::scale(glm::vec3{ 1,1,1 });

		if (inBox) {
			scale = glm::scale(glm::vec3{ 1.5,1.1,1 });
		}
		translate = translate_world * translate_model * scale;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_PauseQuitgame::GetMouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			int worldX = x - WINDOW_WIDTH / 2;
			int worldY = WINDOW_HEIGHT / 2 - y;

			if (vec3_WorldPosition.x - size.x <= worldX && worldX <= vec3_WorldPosition.x + size.x && vec3_WorldPosition.y - size.y <= worldY && worldY <= vec3_WorldPosition.y + size.y) {
				clicked = true;
			}
			else
				clicked = false;
		}
	}
}

void CObject_PauseQuitgame::GetMouseMotion(int x, int y) {
	int worldX = x - WINDOW_WIDTH / 2;
	int worldY = WINDOW_HEIGHT / 2 - y;

	if (vec3_WorldPosition.x - size.x <= worldX && worldX <= vec3_WorldPosition.x + size.x && vec3_WorldPosition.y - size.y <= worldY && worldY <= vec3_WorldPosition.y + size.y) {
		inBox = true;
	}
	else
		inBox = false;

}
