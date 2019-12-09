#pragma once
#include "define.h"
#include "CObject.h"

class CObjectManager {
private:
	std::vector<CObject*> vector_Objects;
	CCamera& camera;
public:
	CObjectManager(CCamera& cam) : camera(cam) { }

	void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f) {
		for (auto iter : vector_Objects)
			iter->Update(lightPos, lightColor, lightPower);
	}

	void Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower) {
		for (auto iter : vector_Objects)
			iter->Update(lightPos, lightColor, lightPower);
	}

	void Draw() {
		for (auto iter : vector_Objects)
			iter->DrawObject();
	}

	int GetState() {
		for (auto iter : vector_Objects) {
			if (iter->GetState() != -1)
				return iter->GetState();
		}
	}

	void GetKeyboard(unsigned int key) {
		for (auto iter : vector_Objects)
			iter->GetKeyboard(key);
	}

	void AddObject(CObject* object) {
		vector_Objects.push_back(object);
	}

	void DeleteObject(CObject* object) {
		for (int i = 0; i < vector_Objects.size(); ++i) {
			if (vector_Objects[i] == object) {
				vector_Objects.erase(vector_Objects.begin() + i);
			}
		}
	}

	void GetMouseMotion(int x, int y) {
		for (auto iter : vector_Objects)
			iter->GetMouseMotion(x, y);
	}

	void GetMouse(int button, int state, int x, int y) {
		for (auto iter : vector_Objects)
			iter->GetMouse(button, state, x, y);
	}

	void DeleteAll() {
		vector_Objects.clear();
	}

	std::vector<CObject*> GetObjects() {
		return vector_Objects;
	}
};