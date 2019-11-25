#include "CObject_cube.h"
#include "CModel_cube.h"

CObject_cube::CObject_cube(CCamera& cam, glm::vec3 size, glm::vec3 pos) : CObject(cam, pos) {
	vector_Model.push_back(new CModel_cube(size));
	vector_ModelPosition.push_back(glm::vec3{ 0,0,0 });


	for (int i = 0; i < vector_Model.size(); ++i) {
		vector_Buffer.push_back(new vec3Buffer[vector_Model[i]->GetLayoutSize()]);
		vector_Buffer[i][BUFFER_VERTEX] = vector_Model[i]->GetVertex();
		vector_Buffer[i][BUFFER_COLOR] = vector_Model[i]->GetColor();
	}

	for (int i = 0; i < vector_Model.size(); ++i)
		vector_Shader.push_back(new CShader(vector_Model[i]->GetLayoutSize(), vector_Buffer[i]));
}

void CObject_cube::Update()
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, camera.GetCameraProj(), mat_Projection, vector_Buffer[i]);
	}
}