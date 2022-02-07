#include "Camera.h"

Camera::Camera(vectorf3 pos, vectorf3 rotation, float fov, float zNear, float zFar, float aspect) {
	this->position = pos;
	this->rotation = rotation;
	this->fov = fov;
	this->zNear = zNear;
	this->zFar = zFar;
	this->aspect = aspect;
}

Camera::~Camera() {

}

matf4x4 Camera::GetVP() {
	matf4x4 out;
	out.Init();
	MatrixOp::translate(out, position * (-1.0f));
	MatrixOp::simple_rotate(out, rotation * (-1.0f));
	MatrixOp::perspective(out, zNear, zFar, aspect, fov);
	return out;
}

float Camera::GetAspect() {
	return aspect;
}