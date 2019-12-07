#pragma once
#include "CModel.h"
#include "CShader.h"
#include "CCamera.h"

class CObject {
protected:
	std::vector<std::unique_ptr<CModel>> vector_Model;
	std::vector<std::unique_ptr<CShader>> vector_Shader;
	std::vector<std::unique_ptr<std::vector<glm::vec3>[]>> vector_Buffer;

	std::vector<glm::vec3> vector_ModelPosition;
	glm::vec3 vec3_WorldPosition;
	glm::mat4 mat_Projection;
	CCamera& camera;

	std::vector< std::pair<int, std::vector<const char*>>> textures;


	bool bool_Delete;

	void SetBuffer();
	void CreateShader();
	void ClearTexture();
	void AddTexture(int modelIndex, std::vector<const char*> textureName);

public:
	CObject(CCamera& cam, glm::vec3 vPos);
	~CObject();
	void SetWorldPosition(glm::vec3 pos);
	glm::vec3 GetWorldPosition();
	virtual void GetKeyboard(unsigned int key);
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	std::vector<glm::vec3>* GetBuffer(int i = 0);
	void DrawObject();
	bool& IsDelete();
};
