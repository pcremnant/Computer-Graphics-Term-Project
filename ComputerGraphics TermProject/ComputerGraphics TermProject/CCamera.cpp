#include "CCamera.h"

#ifdef __define_h_
#define __define_h_
#endif
CCamera::CCamera()
{
	fAngle = 0;
	vDirection = { 0,0,-1 };
	gCamera.push_back({ 0, 0, 2 });
	gCamera.push_back({ 0, 0, 0 });
	gCamera.push_back({ 0, 1, 0 });
	UpdateCamera();

}

glm::vec3& CCamera::GetEye() { return gCamera[CAMERA_EYE]; }
glm::vec3& CCamera::GetAt() { return gCamera[CAMERA_AT]; }
glm::vec3& CCamera::GetUp() { return gCamera[CAMERA_UP]; }
vec3Buffer& CCamera::GetCamera() { return gCamera; }
glm::mat4 CCamera::GetCameraProj() {
	glm::mat4 CameraMat = glm::lookAt(
		gCamera[CAMERA_EYE],
		gCamera[CAMERA_AT],
		gCamera[CAMERA_UP]
	);
	return CameraMat;
}

void CCamera::UpdateCamera()
{
	vDirection.x = glm::sin(fAngle);
	vDirection.z = -glm::cos(fAngle);

	gCamera[CAMERA_AT].x = gCamera[CAMERA_EYE].x + vDirection.x / 10.f;
	gCamera[CAMERA_AT].z = gCamera[CAMERA_EYE].z + vDirection.z / 10.f;
}


void CCamera::Move(unsigned char key)
{
	glm::vec3 tmpDirection;
	switch (key) {
	case 'w':
	case 'W':
		tmpDirection = { vDirection.x / 10,vDirection.y / 10,vDirection.z / 10 };
		gCamera[CAMERA_EYE] += tmpDirection;
		gCamera[CAMERA_AT] += tmpDirection;
		break;
	case 's':
	case 'S':
		tmpDirection = { vDirection.x / 10,vDirection.y / 10,vDirection.z / 10 };
		gCamera[CAMERA_EYE] -= tmpDirection;
		gCamera[CAMERA_AT] -= tmpDirection;
		break;
	case 'a':
	case 'A':
	{
		glm::mat4 scalling{ 0.1f };
		scalling[3][3] = 1.0;
		tmpDirection = scalling * glm::rotate(glm::radians(90.f), glm::vec3{ 0,1,0 }) * glm::vec4{ vDirection,1.0 };
		gCamera[CAMERA_EYE] += tmpDirection;
		gCamera[CAMERA_AT] += tmpDirection;
	}
	break;

	case 'd':
	case 'D': {
		glm::mat4 scalling{ 0.1f };
		scalling[3][3] = 1.0;
		tmpDirection = scalling * glm::rotate(glm::radians(-90.f), glm::vec3{ 0,1,0 }) * glm::vec4{ vDirection,1.0 };
		gCamera[CAMERA_EYE] += tmpDirection;
		gCamera[CAMERA_AT] += tmpDirection;
	}
			  break;
	case 'q':
	case 'Q':
		fAngle -= 0.05f;
		break;
	case 'e':
	case 'E':
		fAngle += 0.05f;
		break;
	case 'r':
	case 'R':
		tmpDirection = { 0,0.05,0 };
		gCamera[CAMERA_EYE] += tmpDirection;
		gCamera[CAMERA_AT] += tmpDirection;
		break;
	case 'f':
	case 'F':
		tmpDirection = { 0,0.05,0 };
		gCamera[CAMERA_EYE] -= tmpDirection;
		gCamera[CAMERA_AT] -= tmpDirection;
		break;
	case '1':
		fAngle = 0;
		vDirection = { 0,0,-1 };
		gCamera[CAMERA_EYE] = { 0, 0, 1 };
		gCamera[CAMERA_AT] = { 0, 0, 0 };
		gCamera[CAMERA_UP] = { 0, 1, 0 };

		for (int i = 0; i < 3; ++i)
			glm::normalize(gCamera[i]);
		break;
	}
	UpdateCamera();
}