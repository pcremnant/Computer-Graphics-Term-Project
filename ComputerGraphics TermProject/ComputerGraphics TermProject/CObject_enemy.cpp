#include "CModel_enemy.h"
#include "CObject_enemy.h"

CObject_enemy::CObject_enemy(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	float_Speed = 0.02;
	changeDirecton = 0;
	short_Hp = 100;
	int_Type = COLLISION_ENEMY;
	vector_Model.emplace_back(std::make_unique<CModel_enemy>(LAYOUT_NORMAL, size,glm::vec3(0,0,1)));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });

	SetBuffer();

	
	CreateShader();
}


void CObject_enemy::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{

	if (changeDirecton < 15)
		vec3_Direction = glm::vec3{ 1,0.5,1 };
	else if (changeDirecton < 30) 
		vec3_Direction = glm::vec3{ 1,-0.5,1 };
	else if (changeDirecton < 45)
		vec3_Direction = glm::vec3{ -1,0.5,1 };
	else if (changeDirecton < 60)
		vec3_Direction = glm::vec3{ -1,-0.5,1 };
	else
		changeDirecton = 0;

	changeDirecton++;

	vec3_WorldPosition += vec3_Direction * glm::vec3{ float_Speed,float_Speed ,float_Speed };
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

std::vector<float> CObject_enemy::GetBoundingBox() {
	// xz 평면 기준 좌표 (y값은 0) - 앞뒤 / 좌우 회전이 생긴다면 수정 요청할 것
	// front_right - back_right - back_left - front_left
	glm::vec3 vertex[8];
	vertex[0] = glm::vec3{ 0.42, 0.0 ,0.2};
	vertex[1] = glm::vec3{ 0.42, 0.0 ,-0.5 };
	vertex[2] = glm::vec3{ -0.42, 0.0 ,-0.5 };
	vertex[3] = glm::vec3{ -0.42, 0.0 ,0.2 };
	vertex[4] = glm::vec3{ 0.42, 1.2 ,0.2 };
	vertex[5] = glm::vec3{ 0.42, 1.2 ,-0.5 };
	vertex[6] = glm::vec3{ -0.42, 1.2 ,-0.5 };
	vertex[7] = glm::vec3{ -0.42, 1.2 ,0.2 };

	// 바운딩 박스를 객체의 좌표로 이동
	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);
	// 만약 객체가 회전 상태면 추가
	// glm::mat4 rotate = glm::rotate(glm::radians(float_WorldAngleY), glm::vec3{ 0,1,0 });
	transform = translate;

	for (auto &iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	// 가장 끝 점들 찾기
	float minX = 0, maxX = 0, minZ = 0, maxZ = 0, minY = 0, maxY = 0;

	for (int i = 0; i < 8; ++i) {
		if (i == 0) {
			minX = vertex[i].x;
			maxX = vertex[i].x;
			minY = vertex[i].y;
			maxY = vertex[i].y;
			minZ = vertex[i].z;
			maxZ = vertex[i].z;
		}
		else {
			if (vertex[i].x < minX)
				minX = vertex[i].x;
			else if (vertex[i].x > maxX)
				maxX = vertex[i].x;
			if (vertex[i].y < minY)
				minY = vertex[i].y;
			else if (vertex[i].y > maxY)
				maxY = vertex[i].y;
			if (vertex[i].z < minZ)
				minZ = vertex[i].z;
			else if (vertex[i].z > maxZ)
				maxZ = vertex[i].z;
		}
	}

	// 벡터에 값 넣고 리턴w
	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(minY);
	collisionbox.emplace_back(maxY);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);
	return collisionbox;
}

void CObject_enemy::Collide(int type) {
	// 충돌판정시에 타입에 따라 행동
	// type -> object에 내장되어있고 객체의 타입을 나타냄
	// 아래처럼 사용 가능
	// CObjectManager 의 CheckCollision을 사용하면 자동으로 값이 들어온다.
	std::cout << "collide" << std::endl;
	switch (type) {
	case COLLISION_BULLET:
		vec3_WorldPosition -= glm::vec3{ 0,0,2 };
		short_Hp -= 50;
		if (short_Hp == 0)
			bool_Delete = true;
		break;
	case COLLISION_BARRIGATE:
		bool_Delete = true;
		break;
	}
}