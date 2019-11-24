#pragma once
#include "define.h"

class CCamera {
private:
	enum { CAMERA_EYE, CAMERA_AT, CAMERA_UP };

	glm::vec3 vDirection;
	GLfloat fAngle;

	vec3Buffer gCamera;
public:
	CCamera();
	glm::vec3& GetEye();
	glm::vec3& GetAt();
	glm::vec3& GetUp();
	vec3Buffer& GetCamera();
	glm::mat4 GetCameraProj();
	void UpdateCamera();
	void Move(unsigned char key);
};
