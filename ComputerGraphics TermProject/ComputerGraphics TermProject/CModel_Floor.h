#pragma once
#pragma once
#include "CModel.h"

class CModel_DownFloor : public CModel {
protected:
	float fSize;
public:
	CModel_DownFloor(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 });
};

class CModel_LeftFloor : public CModel {
protected:
	float fSize;
public:
	CModel_LeftFloor(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 });
};

class CModel_RightFloor : public CModel {
protected:
	float fSize;
public:
	CModel_RightFloor(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 });
};

class CModel_BackFloor : public CModel {
protected:
	float fSize;
public:
	CModel_BackFloor(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 });
};

class CModel_UpFloor : public CModel {
protected:
	float fSize;
public:
	CModel_UpFloor(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 });
};

class CModel_FrontFloor : public CModel {
protected:
	float fSize;
public:
	CModel_FrontFloor(int layout = 3, glm::vec3 size = glm::vec3{ 1,1,1 }, glm::vec3 color = glm::vec3{ 1,1,1 });
};