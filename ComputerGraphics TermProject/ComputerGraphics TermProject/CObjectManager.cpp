#include "CObjectManager.h"

CObjectManager::CObjectManager(CCamera& cam) : camera(cam) { }

void CObjectManager::Update(glm::vec3 lightPos, glm::vec3 lightColor, float lightPower) {

	for (auto iter : vector_Objects)
		iter->Update(lightPos, lightColor, lightPower);

	for (int i = 0; i < vector_Objects.size(); ++i) {
		if (vector_Objects[i]->IsDelete()) {
			DeleteObject(vector_Objects[i]);
		}
	}
}

void CObjectManager::Update(std::vector<glm::vec3> lightPos, std::vector<glm::vec3> lightColor, std::vector<float> lightPower) {
	for (auto iter : vector_Objects)
		iter->Update(lightPos, lightColor, lightPower);

	for (int i = 0; i < vector_Objects.size(); ++i) {
		if (vector_Objects[i]->IsDelete()) {
			DeleteObject(vector_Objects[i]);
		}
	}
}

void CObjectManager::Draw() {
	for (auto iter : vector_Objects)
		iter->DrawObject();
}

int CObjectManager::GetState() {
	for (auto iter : vector_Objects) {
		if (iter->GetState() != -1)
			return iter->GetState();
	}
}

void CObjectManager::GetKeyboard(unsigned int key) {
	for (auto iter : vector_Objects)
		iter->GetKeyboard(key);
}

void CObjectManager::AddObject(CObject* object) {
	vector_Objects.push_back(object);
}

void CObjectManager::DeleteObject(CObject* object) {
	for (int i = 0; i < vector_Objects.size(); ++i) {
		if (vector_Objects[i] == object) {
			delete vector_Objects[i];
			vector_Objects.erase(vector_Objects.begin() + i);
		}
	}
}

void CObjectManager::GetMouseMotion(int x, int y) {
	for (auto iter : vector_Objects)
		iter->GetMouseMotion(x, y);
}

void CObjectManager::GetMouse(int button, int state, int x, int y) {
	for (auto iter : vector_Objects)
		iter->GetMouse(button, state, x, y);
}

void CObjectManager::DeleteAll() {
	vector_Objects.clear();
}

std::vector<CObject*> CObjectManager::GetObjects() {
	return vector_Objects;
}

bool CObjectManager::IsCollide(std::vector<float>& object, std::vector<float>& other) {
	if (object[MAX_X] < other[MIN_X] || object[MIN_X] > other[MAX_X])
		return false;

	if (object[MAX_Y] < other[MIN_Y] || object[MIN_Y] > other[MAX_Y])
		return false;

	if (object[MAX_Z] < other[MIN_Z] || object[MIN_Z] > other[MAX_Z])
		return false;

	return true;
}

void CObjectManager::ChangeFov(glm::mat4 proj) {
	for (auto iter : vector_Objects)
		iter->ChangeFov(proj);
}

std::vector<glm::vec3> CObjectManager::CheckCollision(std::vector<CObject*>& objects, std::vector<CObject*>& others) {
	std::vector<glm::vec3> collidePosition;
	for (auto iter : objects) {
		std::vector<float> box = iter->GetBoundingBox();
		for (auto other : others) {
			std::vector<float> other_box = other->GetBoundingBox();
			if (IsCollide(box, other_box)) {
				collidePosition.emplace_back(iter->GetWorldPosition());
				iter->Collide(other->GetType());
				other->Collide(iter->GetType());
			}
		}
	}
	return collidePosition;
}
