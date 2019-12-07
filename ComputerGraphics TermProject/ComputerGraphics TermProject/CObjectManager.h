#pragma once
#include "define.h"
#include "CObject.h"

class CObjectManager {
private:
	std::vector<CObject*> vector_Objects;
	CCamera& camera;
public:
	CObjectManager(CCamera& cam) : camera(cam) { }

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

	void DeleteAll() {
		vector_Objects.clear();
	}

	std::vector<CObject*> GetObjects() {
		return vector_Objects;
	}
};