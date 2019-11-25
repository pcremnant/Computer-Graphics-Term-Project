#include "CObject_cube.h"
#include "CModel_cube.h"

CObject_cube::CObject_cube(CCamera& cam, glm::vec3 size, glm::vec3 pos) : CObject(cam, pos) {
	vModel.push_back(new CModel_cube(size));
	vModelPosition.push_back(glm::vec3{ 0,0,0 });


	for (int i = 0; i < vModel.size(); ++i) {
		vBuffer.push_back(new vec3Buffer[vModel[i]->GetLayoutSize()]);
		vBuffer[i][BUFFER_VERTEX] = vModel[i]->GetVertex();
		vBuffer[i][BUFFER_COLOR] = vModel[i]->GetColor();
	}

	for (int i = 0; i < vModel.size(); ++i)
		vShader.push_back(new CShader(vModel[i]->GetLayoutSize(), vBuffer[i]));
}

void CObject_cube::Update()
{
	for (int i = 0; i < vModel.size(); ++i) {
		glm::mat4 translate = glm::translate(vModelPosition[i]);
		vShader[i]->Update(translate, camera.GetCameraProj(), mat_Projection, vBuffer[i]);
	}
}