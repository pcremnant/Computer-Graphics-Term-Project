#pragma once
#include "define.h"
#include "CObject_cube.h"

class CObjectManager {
private:
	std::vector<CObject*> vector_Objects;
	CCamera& camera;
public:
	CObjectManager(CCamera& cam) : camera(cam) {
		//vector_Objects.push_back(new CObject_cube(camera, glm::vec3{ 3,0.01,3 }, glm::vec3{ 0,-0.15,0 }));
	}

	void Update() {
		for (auto iter : vector_Objects)
			iter->Update();
	}

	void Draw() {
		for (auto iter : vector_Objects)
			iter->DrawObject();
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

	std::vector<CObject*> GetObjects() {
		return vector_Objects;
	}
};