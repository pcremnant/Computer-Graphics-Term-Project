#include "CObject_aim.h"
#include "CModel_plane.h"

CObject_aim::CObject_aim(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_NORMAL, glm::vec3{20,3, 0},glm::vec3(1,0,0)));
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_NORMAL, glm::vec3{20,3, 0},glm::vec3(1,0,0)));
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_NORMAL, glm::vec3{3,20, 0},glm::vec3(1,0,0)));
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_NORMAL, glm::vec3{3,20, 0},glm::vec3(1,0,0)));

	vector_ModelPosition.emplace_back(glm::vec3{ -30,0,0 });
	vector_ModelPosition.emplace_back(glm::vec3{ 30,0,0 });
	vector_ModelPosition.emplace_back(glm::vec3{ 0,-30,0 });
	vector_ModelPosition.emplace_back(glm::vec3{ 0,30,0 });

	mat4_WorldRotate = glm::mat4{ 1.0f, };
	RotateAngleX = 0;
	RotateAngleY = 0;

	SetBuffer();

	CreateShader();

}

void CObject_aim::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{

	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		glm::mat4 camera_inversed = glm::inverse(camera.GetCameraProj());
		camera_inversed[0][3] = 0;
		camera_inversed[1][3] = 0;
		camera_inversed[2][3] = 0;
		camera_inversed[3][0] = 0;
		camera_inversed[3][1] = 0;
		camera_inversed[3][2] = 0;
		camera_inversed[3][3] = 1;
		translate = translate_world * translate_model * camera_inversed;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_aim::GetKeyboard(unsigned int key) {
	switch (key) {
	case 'a':
	case 'A':
		RotateAngleY -= 2;
		break;
	case 'd':
	case 'D':
		RotateAngleY += 2;
		break;
	case 'w':
	case 'W':
		RotateAngleX += 2;
		break;
	case 's':
	case 'S':
		RotateAngleX -= 2;
		break;
	}
}