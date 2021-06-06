#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

namespace Saturn {

	enum class CameraType {
		PERSPECTIVE,
		ORTHO
	};

	using LookAt = glm::mat4;

	class Camera : public GameObject 
	{
	public:
		Camera(CameraType projectionType, float fov = 60.0f, float zNear = 0.1f, float zFar = 1000.0f);
		~Camera();

		inline float GetFov() const { return c_FieldOfView; }
		inline float GetzNear() const { return c_ZNearVal; }
		inline float GetzFar() const { return c_ZFarVal; }
		inline CameraType GetCameraType() const { return c_CamType; }
		void SetFov(float fov);
		void SetzNear(float zNear);
		void SetzFar(float zFar);
		void SetCameraType(CameraType projectionType);
		LookAt GetLookAt();

	private:
		float c_FieldOfView;
		float c_ZNearVal;
		float c_ZFarVal;
		CameraType c_CamType;
		glm::vec3 c_Forward = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 c_Up = glm::vec3(0.0, 1.0f, 0.0f);
		float c_YRotation = GetTransform().Rotation.y; //Yaw
		float c_XRotation = GetTransform().Rotation.x; //Pitch
	};

}

#endif CAMERA_H