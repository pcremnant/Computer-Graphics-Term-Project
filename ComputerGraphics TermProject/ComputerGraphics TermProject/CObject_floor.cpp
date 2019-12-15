#include "CObject_floor.h"
#include "CModel_Floor.h"

CObject_UpFloor::CObject_UpFloor(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_UpFloor>(LAYOUT_UV, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });


	SetBuffer();
	int_Type = COLLISION_FLOOR;
	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;

	t.emplace_back("./resource/texture/flatrock_up.bmp");

	sz.emplace_back(512, 512);


	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_UpFloor::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_UpFloor::Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

std::vector<float> CObject_UpFloor::GetBoundingBox() {
	glm::vec3 vertex[4];
	vertex[0] = glm::vec3{ 10, 0 ,10 };
	vertex[1] = glm::vec3{ 10, 0 ,-10 };
	vertex[2] = glm::vec3{ -10, 1 ,10 };
	vertex[3] = glm::vec3{ -10, 1 ,-10 };


	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);

	transform = translate;

	for (auto &iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	float minX = 0, maxX = 0, minZ = 0, maxZ = 0, minY = 0, maxY = 0;

	for (int i = 0; i < 4; ++i) {
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

	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(minY);
	collisionbox.emplace_back(maxY);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);
	return collisionbox;
}

void CObject_UpFloor::Collide(int type) {
}










CObject_DownFloor::CObject_DownFloor(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_DownFloor>(LAYOUT_UV, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });


	SetBuffer();
	int_Type = COLLISION_FLOOR;
	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;

	t.emplace_back("./resource/texture/flatrock_dn.bmp");

	sz.emplace_back(512, 512);


	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_DownFloor::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_DownFloor::Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

std::vector<float> CObject_DownFloor::GetBoundingBox() {
	glm::vec3 vertex[4];
	vertex[0] = glm::vec3{ 1000, -1000 ,1000 };
	vertex[1] = glm::vec3{ 1000, -1000,-1000 };
	vertex[2] = glm::vec3{ -1000, 1 ,1000 };
	vertex[3] = glm::vec3{ -1000, 1 ,-1000 };


	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);

	transform = translate;

	for (auto &iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	float minX = 0, maxX = 0, minZ = 0, maxZ = 0, minY = 0, maxY = 0;

	for (int i = 0; i < 4; ++i) {
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

	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(minY);
	collisionbox.emplace_back(maxY);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);
	return collisionbox;
}

void CObject_DownFloor::Collide(int type) {
}











CObject_LeftFloor::CObject_LeftFloor(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_LeftFloor>(LAYOUT_UV, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0});

	SetBuffer();
	int_Type = COLLISION_FLOOR;
	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;


	t.emplace_back("./resource/texture/flatrock_lf.bmp");

	sz.emplace_back(512, 512);

	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_LeftFloor::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_LeftFloor::Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

std::vector<float> CObject_LeftFloor::GetBoundingBox() {
	glm::vec3 vertex[4];
	vertex[0] = glm::vec3{ 0,10 ,10 };
	vertex[1] = glm::vec3{ 0,10 ,-10 };
	vertex[2] = glm::vec3{ 1,-10 ,10 };
	vertex[3] = glm::vec3{ 1,-10 ,-10 };


	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);

	transform = translate;

	for (auto &iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	float minX = 0, maxX = 0, minZ = 0, maxZ = 0, minY = 0, maxY = 0;

	for (int i = 0; i < 4; ++i) {
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

	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(minY);
	collisionbox.emplace_back(maxY);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);
	return collisionbox;
}

void CObject_LeftFloor::Collide(int type) {
}



CObject_RightFloor::CObject_RightFloor(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_RightFloor>(LAYOUT_UV, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });

	SetBuffer();
	int_Type = COLLISION_FLOOR;
	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;


	t.emplace_back("./resource/texture/flatrock_rt.bmp");

	sz.emplace_back(512, 512);

	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_RightFloor::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_RightFloor::Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}


std::vector<float> CObject_RightFloor::GetBoundingBox() {
	glm::vec3 vertex[4];
	vertex[0] = glm::vec3{ 0,10 ,10 };
	vertex[1] = glm::vec3{ 0,10 ,-10 };
	vertex[2] = glm::vec3{ 1,-10 ,10 };
	vertex[3] = glm::vec3{ 1,-10 ,-10 };


	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);

	transform = translate;

	for (auto &iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	float minX = 0, maxX = 0, minZ = 0, maxZ = 0, minY = 0, maxY = 0;

	for (int i = 0; i < 4; ++i) {
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

	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(minY);
	collisionbox.emplace_back(maxY);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);
	return collisionbox;
}

void CObject_RightFloor::Collide(int type) {
}



CObject_BackFloor::CObject_BackFloor(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_BackFloor>(LAYOUT_UV, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });

	SetBuffer();
	int_Type = COLLISION_FLOOR;
	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;


	t.emplace_back("./resource/texture/flatrock_bk.bmp");

	sz.emplace_back(512, 512);

	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_BackFloor::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_BackFloor::Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}


std::vector<float> CObject_BackFloor::GetBoundingBox() {
	glm::vec3 vertex[4];
	vertex[0] = glm::vec3{ 10,10 ,0 };
	vertex[1] = glm::vec3{ 10,-10 ,0 };
	vertex[2] = glm::vec3{ -10,10 ,1};
	vertex[3] = glm::vec3{ -10,-10 ,1};


	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);

	transform = translate;

	for (auto &iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	float minX = 0, maxX = 0, minZ = 0, maxZ = 0, minY = 0, maxY = 0;

	for (int i = 0; i < 4; ++i) {
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

	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(minY);
	collisionbox.emplace_back(maxY);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);
	return collisionbox;
}

void CObject_BackFloor::Collide(int type) {
}









CObject_FrontFloor::CObject_FrontFloor(CCamera& cam, glm::vec3 size, glm::vec3 pos, glm::mat4 proj) : CObject(cam, pos, proj) {
	vector_Model.emplace_back(std::make_unique<CModel_FrontFloor>(LAYOUT_UV, size));

	vector_ModelPosition.emplace_back(glm::vec3{ 0,0,0 });

	int_Type = COLLISION_FLOOR;
	SetBuffer();

	std::vector<const char*> t;
	std::vector<std::pair<int, int>> sz;

	t.emplace_back("./resource/texture/flatrock_ft.bmp");

	sz.emplace_back(512, 512);


	AddTexture(0, t, sz);

	CreateShader();

}

void CObject_FrontFloor::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

void CObject_FrontFloor::Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower)
{
	for (int i = 0; i < vector_Model.size(); ++i) {
		glm::mat4 translate = glm::mat4{ 1, };
		glm::mat4 translate_model = glm::translate(vector_ModelPosition[i]);
		glm::mat4 translate_world = glm::translate(vec3_WorldPosition);
		translate = translate_world * translate_model;
		vector_Shader[i]->Update(translate, vector_Buffer[i].get(), lightPos, lightColor, lightPower);
	}
}

std::vector<float> CObject_FrontFloor::GetBoundingBox() {
	glm::vec3 vertex[4];
	vertex[0] = glm::vec3{ 10,10 ,0 };
	vertex[1] = glm::vec3{ 10,-10 ,0 };
	vertex[2] = glm::vec3{ -10,10 ,1 };
	vertex[3] = glm::vec3{ -10,-10 ,1 };


	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 translate = glm::translate(vec3_WorldPosition);

	transform = translate;

	for (auto &iter : vertex) {
		iter = transform * glm::vec4{ iter,1 };
	}


	float minX = 0, maxX = 0, minZ = 0, maxZ = 0, minY = 0, maxY = 0;

	for (int i = 0; i < 4; ++i) {
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

	std::vector<float> collisionbox;
	collisionbox.emplace_back(minX);
	collisionbox.emplace_back(maxX);
	collisionbox.emplace_back(minY);
	collisionbox.emplace_back(maxY);
	collisionbox.emplace_back(minZ);
	collisionbox.emplace_back(maxZ);
	return collisionbox;
}

void CObject_FrontFloor::Collide(int type) {
}
