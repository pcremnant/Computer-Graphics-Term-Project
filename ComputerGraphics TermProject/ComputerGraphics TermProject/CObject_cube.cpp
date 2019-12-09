#include "CObject_cube.h"
#include "CModel_cube.h"

CObject_cube::CObject_cube(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_cube>(4, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });


	SetBuffer();

	std::vector<const char*> s;
	std::vector<std::pair<int, int>> z;
	s.emplace_back("resource/texture/texture_1.bmp");
	z.emplace_back(256, 256);
	AddTexture(0, s, z);

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


// 숙제2의 충돌판정임 - 보고 참고할 것
std::vector<float> CObject_cube::GetBoundingBox() {
	// xz 평면 기준 좌표 (y값은 0) - 앞뒤 / 좌우 회전이 생긴다면 수정 요청할 것
	// front_right - back_right - back_left - front_left
	glm::vec3 vertex[4];
	vertex[0] = glm::vec3{ 0.15, 0.0 ,0.1 };
	vertex[1] = glm::vec3{ 0.15, 0.0 ,-0.1 };
	vertex[2] = glm::vec3{ -0.15, 0.0 ,-0.1 };
	vertex[3] = glm::vec3{ -0.15, 0.0 ,0.1 };

	// 바운딩 박스를 객체의 좌표로 이동
	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);
	// 만약 객체가 회전 상태면 추가
	// glm::mat4 rotate = glm::rotate(glm::radians(float_WorldAngleY), glm::vec3{ 0,1,0 });
	transform = translate;

	for (auto iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	// 가장 끝 점들 찾기
	float minX = 0, maxX = 0, minZ = 0, maxZ = 0;

	for (int i = 0; i < 4; ++i) {
		if (i == 0) {
			minX = vertex[i].x;
			maxX = vertex[i].x;
			minZ = vertex[i].z;;
			maxZ = vertex[i].z;;
		}
		else {
			if (vertex[i].x < minX)
				minX = vertex[i].x;
			else if (vertex[i].x > maxX)
				maxX = vertex[i].x;
			if (vertex[i].z < minZ)
				minZ = vertex[i].z;
			else if (vertex[i].z > maxZ)
				maxZ = vertex[i].z;
		}
	}

	// 벡터에 값 넣고 리턴
	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(vec3_WorldPosition.y - 0.35);
	collisionbox.emplace_back(vec3_WorldPosition.y + 0.35);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);

	return collisionbox;
}

void CObject_cube::Collide(int type) {
	// 충돌판정시에 타입에 따라 행동
	// type -> object에 내장되어있고 객체의 타입을 나타냄
	// 아래처럼 사용 가능
	// CObjectManager 의 CheckCollision을 사용하면 자동으로 값이 들어온다.

	//switch (type) {
	//case COLLISION_NONE:
	//	bool_ColideFloor = false;
	//	break;
	//case COLLISION_FLOOR:
	//	bool_ColideFloor = true;
	//	break;
	//}
}