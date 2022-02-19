#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"

class Camera {
public:
	Camera(vectorf3 pos, vectorf3 rotation, float fov, float zNear, float zFar, float aspect);
	~Camera();
	matf4x4 GetVP();
	float GetAspect();
	void Move(vectori2 dir, float del);
private:
	vectorf3 position;
	vectorf3 rotation;
	float fov;
	float zNear;
	float zFar;
	float aspect;
};

#endif