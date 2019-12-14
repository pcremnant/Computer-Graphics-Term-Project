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

	bool IsCollide(std::vector<float>& object, std::vector<float>& other) {
		if (object[MAX_X] < other[MIN_X] || object[MIN_X] > other[MAX_X])
			return false;

		if (object[MAX_Y] < other[MIN_Y] || object[MIN_Y] > other[MAX_Y])
			return false;

		if (object[MAX_Z] < other[MIN_Y] || object[MIN_Z] > other[MAX_Z])
			return false;

		return true;
	}

	void CheckCollision(std::vector<CObject*>& objects, std::vector<CObject*>& others) {
		for (auto iter : objects) {
			std::vector<float> box = iter->GetBoundingBox();
			for (auto other : others) {
				std::vector<float> other_box = other->GetBoundingBox();
				if (IsCollide(box, other_box)) {
					iter->Collide(other->GetType());
					other->Collide(iter->GetType());
				}
			}
		}
	}
};