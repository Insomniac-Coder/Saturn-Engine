#include "Camera.h"

Saturn::Camera::Camera(CameraType projectionType, float fov, float zNear, float zFar) : c_CamType(projectionType), c_FieldOfView(fov), c_ZNearVal(zNear), c_ZFarVal(zFar)
{
	SetRotation(Rotation(0.0f, 0.0f, 0.0f));
}

Saturn::Camera::~Camera()
{
}

void Saturn::Camera::SetFov(float fov)
{
	c_FieldOfView = fov;
}

void Saturn::Camera::SetzNear(float zNear)
{
	c_ZNearVal = zNear;
}

void Saturn::Camera::SetzFar(float zFar)
{
	c_ZFarVal = zFar;
}

void Saturn::Camera::SetCameraType(CameraType projectionType)
{
	c_CamType = projectionType;
}

Saturn::LookAt Saturn::Camera::GetLookAt()
{
	c_YRotation = GetTransform().Rotation.y;
	c_XRotation = GetTransform().Rotation.x;
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(c_YRotation -90.0f)) * cos(glm::radians(c_XRotation));
	front.y = sin(glm::radians(c_XRotation));
	front.z = sin(glm::radians(c_YRotation -90.0f)) * cos(glm::radians(c_XRotation));

	c_Forward = glm::normalize(front);
	// also re-calculate the Right and Up vector
	glm::vec3 Right = glm::normalize(glm::cross(c_Forward, c_Up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	c_Up = glm::normalize(glm::cross(Right, c_Forward));

	return glm::lookAt(GetTransform().Position, GetTransform().Position + c_Forward, c_Up); 
}