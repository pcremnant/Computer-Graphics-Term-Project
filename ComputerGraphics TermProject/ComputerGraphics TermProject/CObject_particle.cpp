#include "CObject_Particle.h"
#include "CModel_plane.h"

CObject_Particle::CObject_Particle(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	bool_Delete = false;
	frameNumber = std::make_pair(5, 5);
	int_Frame = 0;

	vector_Model.emplace_back(std::make_unique<CModel_plane>(LAYOUT_UI, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });

	vector_Model[0]->SetFrame(int_Frame, frameNumber);

	SetBuffer();

	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;

	t.emplace_back("./resource/texture/particle.bmp");
	sz.emplace_back(512, 512);

	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_Particle::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	int_Frame++;
	if (int_Frame >= frameNumber.first * frameNumber.second - 1)
		int_Frame = 0;

	vector_Model[0]->SetFrame(int_Frame, frameNumber);

	vector_Buffer.clear();
	SetBuffer();
	vector_Buffer[0].get()[LAYOUT_UV] = vector_Model[0]->GetUv();

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
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower, glm::vec3{ 0,0,0 });
	}
}