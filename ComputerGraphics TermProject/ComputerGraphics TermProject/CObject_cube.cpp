#include "CObject_cube.h"
#include "CModel_cube.h"

CObject_cube::CObject_cube(CCamera& cam, glm::vec3 size, glm::vec3 pos) : CObject(cam, pos) {
	pModel = new CModel_cube(size);

	pBuffer = new vec3Buffer[pModel->GetLayoutSize()];
	pBuffer[BUFFER_VERTEX] = pModel->GetVertex();
	pBuffer[BUFFER_COLOR] = pModel->GetColor();

	pShader = new CShader(pModel->GetLayoutSize(), pBuffer);
}

void CObject_cube::Update()
{
	glm::mat4 translate = glm::translate(vWorldPosition);
	pShader->Update(translate, camera.GetCameraProj(), mat_Projection, pBuffer);
}