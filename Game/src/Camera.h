#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"

class Camera {
public:
	Camera(vectorf3 pos, vectorf3 rotation, float fov, float zNear, float zFar, float aspect);
	~Camera();
	matf4x4 GetVP();
	float GetAspect();
private:
	vectorf3 position;
	vectorf3 rotation;
	float fov;
	float zNear;
	float zFar;
	float aspect;
};

#endif