#include "CObject_cube.h"
#include "CModel_cube.h"

CObject_cube::CObject_cube(CCamera& cam, glm::vec3 size, glm::vec3 pos) : CObject(cam, pos) {
	vector_Model.emplace_back(std::make_unique<CModel_cube>(3, size));
	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });


	SetBuffer();

	//std::vector<const char*> s;
	//s.emplace_back("texture_1.bmp");
	//s.emplace_back("texture_2.bmp");
	//s.emplace_back("texture_3.bmp");
	//s.emplace_back("texture_4.bmp");
	//s.emplace_back("texture_5.bmp");
	//s.emplace_back("texture_6.bmp");
	//
	//AddTexture(0, s);

	CreateShader();

}

void CObject_cube::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}