#ifndef MATH_H
#define MATH_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>

struct vectorf2 {
	float x;
	float y;
	vectorf2();
	vectorf2(float x, float y);
	void SetValue(float x, float y);
	vectorf2 operator*(float val);
	vectorf2 operator+(vectorf2 other);
	vectorf2 operator-(vectorf2 other);
};

struct vectori2 {
	int x;
	int y;
	vectori2();
	vectori2(int x, int y);
	vectori2(std::pair<int, int> val);
	void SetValue(int x, int y);
	vectori2 operator*(int val);
	vectori2 operator+(vectori2 other);
	operator std::pair<int, int>();
};

struct vectorf3 {
	float x;
	float y;
	float z;
	vectorf3();
	vectorf3(float x, float y, float z);
	void SetValue(float x, float y, float z);
	vectorf3 operator*(float val);
	vectorf3 operator+(vectorf3 other);
};

struct matf4x4 {
	float mas[4*4];
	matf4x4 operator*(const matf4x4& other);
	void Init();
};

class MatrixOp {
public:
	static void translate(matf4x4& mat, vectorf3 vec);
	static void simple_rotate(matf4x4& mat, vectorf3 angles);
	static void perspective(matf4x4& mat, float Near, float Far, float aspect, float fov);
};

#endif