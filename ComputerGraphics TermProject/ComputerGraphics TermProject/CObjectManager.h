#pragma once
#include "define.h"
#include "CObject.h"

#define MIN_X 0
#define MAX_X 1

#define MIN_Y 2
#define MAX_Y 3

#define MIN_Z 4
#define MAX_Z 5

class CObjectManager {
private:
	std::vector<CObject*> vector_Objects;
	CCamera& camera;
public:
	CObjectManager(CCamera& cam);

	void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);

	void Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower);

	void Draw();

	int GetState();

	void GetKeyboard(unsigned int key);

	void AddObject(CObject* object);

	void DeleteObject(CObject* object);

	void GetMouseMotion(int x, int y);

	void GetMouse(int button, int state, int x, int y);

	void DeleteAll();

	std::vector<CObject*> GetObjects();

	bool IsCollide(std::vector<float>& object, std::vector<float>& other);

	void ChangeFov(glm::mat4 proj);

	std::vector<glm::vec3> CheckCollision(std::vector<CObject*>& objects, std::vector<CObject*>& others);
};