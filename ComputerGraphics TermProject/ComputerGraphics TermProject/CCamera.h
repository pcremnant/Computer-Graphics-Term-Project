#pragma once
#include "define.h"

class CCamera {
private:
	enum { CAMERA_EYE, CAMERA_AT, CAMERA_UP };

	glm::vec3 vec3_Direction;
	GLfloat float_AngleY;
	GLfloat float_AngleX;

	vec3Buffer vector_Camera;

	void SetDirection();
	void MoveToFront();
	void MoveToBehind();
	void MoveToRight();
	void MoveToLeft();
	void MoveToUp();
	void MoveToDown();
	void RotateClockwise();
	void RotateCounterClockWise();
	void RotateUp();
	void RotateDown();

	void InitCamera();

public:
	CCamera();
	glm::vec3& GetEye();
	glm::vec3& GetAt();
	glm::vec3& GetUp();
	vec3Buffer& GetCamera();
	glm::vec3 GetDirection();
	float GetAngleY() const;
	float GetAngleZ() const;
	glm::mat4 GetCameraProj();
	void UpdateCamera();
	void Move(unsigned char key);
};
