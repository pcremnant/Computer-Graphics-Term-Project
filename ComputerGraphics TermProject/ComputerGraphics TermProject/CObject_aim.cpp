#include "CObject_aim.h"
#include "CModel_plane.h"

CObject_aim::CObject_aim(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_UI, glm::vec3{0.1,0.1, 0},glm::vec3(1,0,0)));


	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });


	mat4_WorldRotate = glm::mat4{ 1.0f, };
	RotateAngleX = 0;
	RotateAngleY = 0;

	SetBuffer();
	CreateShader();

}

void CObject_aim::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	vec3_WorldPosition = camera.GetAt();


	for (int i = 0; i < vector_Model.size(); ++i) {
		vector_Shader[i]->Update(glm::vec3{ 1,1,1 }, glm::vec3{ 0,0,0 }, vector_Buffer[i].get());
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