#include "CCamera.h"

CCamera::CCamera()
{
	float_AngleY = 270;
	float_AngleX = 0;
	SetDirection();
	vector_Camera.push_back({ 0, 0, 2 });
	vector_Camera.push_back(vector_Camera[CAMERA_EYE] + vec3_Direction);

	glm::vec3 right = glm::vec3{ glm::cos(glm::radians(float_AngleY - 90)),0,glm::sin(glm::radians(float_AngleY - 90)) };
	vector_Camera.push_back(glm::normalize(glm::cross(right, vec3_Direction)));
	UpdateCamera();
}

void CCamera::SetDirection()
{
	vec3_Direction = glm::vec3{ glm::cos(glm::radians(float_AngleY)),0,glm::sin(glm::radians(float_AngleY)) };
	glm::vec3 right = glm::vec3{ glm::cos(glm::radians(float_AngleY - 90)),0,glm::sin(glm::radians(float_AngleY - 90)) };
	vec3_Direction = glm::vec4{ vec3_Direction, 1 } *glm::rotate(glm::mat4{ 1.0, }, glm::radians(float_AngleX), right);
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
	SetDirection();
	vector_Camera[CAMERA_AT] = vector_Camera[CAMERA_EYE] + vec3_Direction;

	glm::vec3 right = glm::vec3{ glm::cos(glm::radians(float_AngleY - 90)),0,glm::sin(glm::radians(float_AngleY - 90)) };

	vector_Camera[CAMERA_UP] = glm::normalize(glm::cross(vec3_Direction, right));
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
	tmpDirection = glm::vec3{ glm::cos(glm::radians(float_AngleY + 90)) / 10,0,glm::sin(glm::radians(float_AngleY + 90)) / 10 };


	vector_Camera[CAMERA_EYE] += tmpDirection;
	vector_Camera[CAMERA_AT] += tmpDirection;
}

void CCamera::MoveToLeft()
{
	glm::vec3 tmpDirection;
	tmpDirection = glm::vec3{ glm::cos(glm::radians(float_AngleY - 90)) / 10,0,glm::sin(glm::radians(float_AngleY - 90)) / 10 };
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
	float_AngleY += 1;
}

void CCamera::RotateCounterClockWise()
{
	float_AngleY -= 1;
}

void CCamera::RotateUp()
{
	float_AngleX += 1;
}
void CCamera::RotateDown()
{
	float_AngleX -= 1;
}

void CCamera::InitCamera()
{
	float_AngleY = 0;
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
	case 'r':
	case 'R':
		MoveToUp();
		break;
	case 'f':
	case 'F':
		MoveToDown();
		break;
	case 't':
	case 'T':
		RotateUp();
		break;
	case 'g':
	case 'G':
		RotateDown();
		break;
	}
	UpdateCamera();
}