#include "CObject_light.h"
#include "CModel_cube.h"

CObject_light::CObject_light(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::vec3 color, float power, glm::mat4 proj) : CObject(cam, pos, proj), fLightPower(power) {
	vector_Model.emplace_back(std::make_unique <CModel_cube>(3, size, color));
	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });

	bLightOn = true;

	SetBuffer();

	CreateShader();
}

void CObject_light::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{

	//vec3_WorldPosition = glm::vec3{ glm::cos(glm::radians(fAngleZ)) * fRadius, glm::sin(glm::radians(fAngleZ)) * fRadius,0 };

	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_light::GetKeyboard(unsigned int key)
{
	switch (key) {
	case 'm':
	case 'M':
		if (bLightOn) {
			for (auto& iter : vector_Buffer[0][1])
				iter = glm::vec3{ 0,0,0 };
		}
		else {
			for (auto& iter : vector_Buffer[0][1]) {
				iter = glm::vec3{ 1,1,1 };
			}
		}
		bLightOn = !bLightOn;
		break;
	}
}

float CObject_light::GetLightPower() const {
	return fLightPower;
}
