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
	std::vector<std::pair<int, std::vector<std::pair<int, int>>>> textureSizes;

	int int_Type{ 0 };
	bool bool_Delete;

	void SetBuffer();
	void CreateShader();
	void ClearTexture();
	void AddTexture(int modelIndex, std::vector<const char*> textureName, std::vector<std::pair<int,int>> textureSize);

public:
	CObject(CCamera& cam, glm::vec3 vPos, glm::mat4 proj = PROJ(60.f));
	~CObject();
	void SetWorldPosition(glm::vec3 pos);
	glm::vec3 GetWorldPosition();
	virtual void GetKeyboard(unsigned int key);
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual void Update(std::vector<glm::vec3> lightPos = std::vector<glm::vec3>(), std::vector<glm::vec3> lightColor = std::vector<glm::vec3>(), std::vector<float> lightPower = std::vector<float>());
	virtual void GetMouse(int button, int state, int x, int y);
	virtual void GetMouseMotion(int x, int y);
	virtual void GetSpecialKeyboard(int key);

	virtual std::vector<float> GetBoundingBox();
	virtual void ChangeFov(glm::mat4 proj = PROJ(60.f));

	virtual void Collide(int type = 0);
	int GetType() const;
	virtual short GetHp();
	std::vector<glm::vec3>* GetBuffer(int i = 0);
	void DrawObject();
	bool& IsDelete();
	virtual int GetState() { return -1; }
};
