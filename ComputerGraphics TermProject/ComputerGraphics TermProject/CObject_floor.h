#pragma once
#include "CObject.h"

class CObject_UpFloor : public CObject {
protected:
public:
	CObject_UpFloor(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};

class CObject_DownFloor : public CObject {
protected:
public:
	CObject_DownFloor(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};

class CObject_LeftFloor : public CObject {
protected:
public:
	CObject_LeftFloor(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};

class CObject_RightFloor : public CObject {
protected:
public:
	CObject_RightFloor(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};

class CObject_BackFloor : public CObject {
protected:
public:
	CObject_BackFloor(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};


class CObject_FrontFloor : public CObject {
protected:
public:
	CObject_FrontFloor(CCamera& cam, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 pos = glm::vec3{ 0,0,0 }, glm::mat4 proj = PROJ(60.f));
	virtual void Update(glm::vec3 lightPos = glm::vec3{ 0,0,0 }, glm::vec3 lightColor = glm::vec3{ 1,1,1 }, float lightPower = 1000.f);
	virtual std::vector<float> GetBoundingBox() final;
	virtual void Collide(int type) final;
};