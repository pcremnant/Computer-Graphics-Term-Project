#include "CCamera.h"

CCamera::CCamera()
{
	float_RotateAngle = 270;
	float_Angle = 0;
	vec3_Direction = { 0,0,-1 };
	vector_Camera.push_back({ 0, 0, 2 });
	vector_Camera.push_back(vector_Camera[CAMERA_EYE] + vec3_Direction);
	vector_Camera.push_back(glm::vec3{ 0,1,0 });
	UpdateCamera();
}

glm::vec3& CCamera::GetEye() { return vector_Camera[CAMERA_EYE]; }
glm::vec3& CCamera::GetAt() { return vector_Camera[CAMERA_AT]; }
glm::vec3& CCamera::GetUp() { return vector_Camera[CAMERA_UP]; }
vec3Buffer& CCamera::GetCamera() { return vector_Camera; }
glm::mat4 CCamera::GetCameraProj() {
	glm::mat4 CameraMat = glm::lookAt(
		vector_Camera[CAMERA_EYE],
		vector_Camera[CAMERA_AT],
		vector_Camera[CAMERA_UP]
	);
	return CameraMat;
}

void CCamera::UpdateCamera()
{
	vector_Camera[CAMERA_AT] = vector_Camera[CAMERA_EYE] + vec3_Direction;
}

void CCamera::MoveToFront()
{
	glm::vec3 tmpDirection;
	tmpDirection = { vec3_Direction.x / 10,vec3_Direction.y / 10,vec3_Direction.z / 10 };
	vector_Camera[CAMERA_EYE] += tmpDirection;
	vector_Camera[CAMERA_AT] += tmpDirection;
}

void CCamera::MoveToBehind()
{
	glm::vec3 tmpDirection;
	tmpDirection = { vec3_Direction.x / 10,vec3_Direction.y / 10,vec3_Direction.z / 10 };
	vector_Camera[CAMERA_EYE] -= tmpDirection;
	vector_Camera[CAMERA_AT] -= tmpDirection;
}

void CCamera::MoveToRight()
{
	glm::vec3 tmpDirection;
	glm::mat4 scalling{ 0.1f };
	scalling[3][3] = 1.0;
	tmpDirection = scalling * glm::rotate(glm::radians(-90.f), glm::vec3{ 0,1,0 }) * glm::vec4{ vec3_Direction,1.0 };
	vector_Camera[CAMERA_EYE] += tmpDirection;
	vector_Camera[CAMERA_AT] += tmpDirection;
}

void CCamera::MoveToLeft()
{
	glm::vec3 tmpDirection;
	glm::mat4 scalling{ 0.1f };
	scalling[3][3] = 1.0;
	tmpDirection = scalling * glm::rotate(glm::radians(90.f), glm::vec3{ 0,1,0 }) * glm::vec4{ vec3_Direction,1.0 };
	vector_Camera[CAMERA_EYE] += tmpDirection;
	vector_Camera[CAMERA_AT] += tmpDirection;
}

void CCamera::MoveToUp()
{
	glm::vec3 tmpDirection;
	tmpDirection = { 0,0.05,0 };
	vector_Camera[CAMERA_EYE] += tmpDirection;
	vector_Camera[CAMERA_AT] += tmpDirection;
}

void CCamera::MoveToDown()
{
	glm::vec3 tmpDirection;
	tmpDirection = { 0,0.05,0 };
	vector_Camera[CAMERA_EYE] -= tmpDirection;
	vector_Camera[CAMERA_AT] -= tmpDirection;
}

void CCamera::RotateClockwise()
{
	float_Angle -= 0.05f;
}

void CCamera::RotateCounterClockWise()
{
	float_Angle += 0.05f;
}

void CCamera::InitCamera()
{
	float_Angle = 0;
	float_RotateAngle = 270;
	vec3_Direction = { 0,0,-1 };
	vector_Camera[CAMERA_EYE] = { 0, 0, 2 };
	vector_Camera[CAMERA_AT] = { 0, 0, 0 };
	vector_Camera[CAMERA_UP] = { 0, 1, 0 };
	UpdateCamera();
}

void CCamera::Move(unsigned char key)
{

	switch (key) {
	case 'w':
	case 'W':
		MoveToFront();
		break;
	case 's':
	case 'S':
		MoveToBehind();
		break;
	case 'a':
	case 'A':
		MoveToLeft();
		break;
	case 'd':
	case 'D':
		MoveToRight();
		break;
	case 'e':
	case 'E':
		RotateClockwise();
		break;
	case 'q':
	case 'Q':
		RotateCounterClockWise();
		break;


	}
	UpdateCamera();
}