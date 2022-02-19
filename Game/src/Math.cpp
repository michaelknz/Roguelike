#include "Math.h"

vectorf2::vectorf2() {
	SetValue(0.0f, 0.0f);
}

vectorf2::vectorf2(float x, float y) {
	SetValue(x, y);
}

void vectorf2::SetValue(float x, float y) {
	this->x = x;
	this->y = y;
}

vectorf2 vectorf2::operator*(float val) {
	vectorf2 out;
	out.x = x * val;
	out.y = y * val;
	return out;
}

vectorf2 vectorf2::operator+(vectorf2 other) {
	return vectorf2(this->x + other.x, this->y + other.y);
}

vectorf2 vectorf2::operator-(vectorf2 other) {
	return vectorf2(this->x - other.x, this->y - other.y);
}

vectori2::vectori2() {
	SetValue(0, 0);
}

vectori2::vectori2(int x, int y) {
	SetValue(x, y);
}

vectori2::vectori2(std::pair<int, int> val) {
	SetValue(val.first, val.second);
}

void vectori2::SetValue(int x, int y) {
	this->x = x;
	this->y = y;
}

vectori2 vectori2::operator*(int val) {
	vectori2 out;
	out.x = val * this->x;
	out.y = val * this->y;
	return out;
}

vectori2 vectori2::operator+(vectori2 other) {
	return vectori2(this->x + other.x, this->y + other.y);
}

vectori2::operator std::pair<int, int>() {
	return std::pair<int, int>(this->x, this->y);
}

vectorf3::vectorf3() {
	SetValue(0.0f, 0.0f, 0.0f);
}

vectorf3::vectorf3(float x, float y, float z) {
	SetValue(x, y, z);
}

void vectorf3::SetValue(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vectorf3 vectorf3::operator*(float val) {
	vectorf3 out;
	out.x = x * val;
	out.y = y * val;
	out.z = z * val;
	return out;
}

vectorf3 vectorf3::operator+(vectorf3 other) {
	return vectorf3(this->x + other.x, this->y + other.y, this->z + other.z);
}

void matf4x4::Init() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mas[i * 4 + j] = float(i == j);
		}
	}
}

matf4x4 matf4x4::operator*(const matf4x4& other) {
	matf4x4 out;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float a = 0;
			for (int k = 0; k < 4; ++k) {
				a += mas[i * 4 + k] * other.mas[k * 4 + j];
			}
			out.mas[i * 4 + j] = a;
		}
	}
	return out;
}

void MatrixOp::translate(matf4x4& mat, vectorf3 vec) {
	matf4x4 mat1;
	mat1.Init();
	mat1.mas[3] = vec.x;
	mat1.mas[7] = vec.y;
	mat1.mas[11] = vec.z;
	mat = mat1 * mat;
}

void MatrixOp::simple_rotate(matf4x4& mat, vectorf3 angles) {
	matf4x4 mat_x;
	matf4x4 mat_y;
	matf4x4 mat_z;
	mat_x.Init();
	mat_y.Init();
	mat_z.Init();

	mat_x.mas[5] = cos((M_PI / 180.0f) * angles.x);
	mat_x.mas[6] = sin((M_PI / 180.0f) * angles.x);
	mat_x.mas[9] = -sin((M_PI / 180.0f) * angles.x);
	mat_x.mas[10] = cos((M_PI / 180.0f) * angles.x);

	mat_y.mas[0] = cos((M_PI / 180.0f) * angles.y);
	mat_y.mas[2] = -sin((M_PI / 180.0f) * angles.y);
	mat_y.mas[8] = sin((M_PI / 180.0f) * angles.y);
	mat_y.mas[10] = cos((M_PI / 180.0f) * angles.y);

	mat_z.mas[0] = cos((M_PI / 180.0f) * angles.z);
	mat_z.mas[1] = sin((M_PI / 180.0f) * angles.z);
	mat_z.mas[4] = -sin((M_PI / 180.0f) * angles.z);
	mat_z.mas[5] = cos((M_PI / 180.0f) * angles.z);

	mat = (mat_x * mat_y * mat_z) * mat;
}

void MatrixOp::perspective(matf4x4& mat, float Near, float Far, float aspect, float fov) {
	matf4x4 mat1;
	mat1.Init();
	mat1.mas[0] = 1.0f / (aspect * tan((M_PI / 360.0f) * fov));
	mat1.mas[5] = 1.0f / tan((M_PI / 360.0f) * fov);
	mat1.mas[10] = (Far + Near) / (Far - Near);
	mat1.mas[11] = (-2 * Far * Near) / (Far - Near);
	mat1.mas[14] = 1.0f;
	mat = mat1 * mat;
}