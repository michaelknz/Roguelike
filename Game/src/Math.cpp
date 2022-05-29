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

Circle::Circle(vectorf2 center, float radius) {
	this->center = center;
	this->radius = radius;
}

Circle::Circle() {
	this->center = vectorf2();
	this->radius = 0.0f;
}

Rectangle::Rectangle(vectorf2 point1, vectorf2 point2, vectorf2 point3, vectorf2 point4) {
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	this->point4 = point4;
}

Rectangle::Rectangle() {
	this->point1 = vectorf2();
	this->point2 = vectorf2();
	this->point3 = vectorf2();
	this->point4 = vectorf2();
}

bool GeometryOp::CircleWithLine(const Circle& circle, vectorf2 point1, vectorf2 point2) {
	float a = (point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y);
	float b = 2.0f * ((point2.x - point1.x) * (point1.x - circle.center.x) + (point2.y - point1.y) * (point1.y - circle.center.y));
	float c = (point1.x - circle.center.x) * (point1.x - circle.center.x) + (point1.y - circle.center.y) * (point1.y - circle.center.y) - circle.radius * circle.radius;
	float d = b * b - 4 * a * c;
	if (d < 0) {
		return false;
	}
	float t1 = (-b + sqrt(d)) / (2 * a);
	float t2 = (-b - sqrt(d)) / (2 * a);
	return ((t1 >= 0.0f && t1 <= 1.0f) || (t2 >= 0.0f && t2 <= 1.0f));
}

float GeometryOp::Dot(vectorf2 v1, vectorf2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

float GeometryOp::Cross(vectorf2 v1, vectorf2 v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

bool GeometryOp::CircleWithCircle(const Circle& circle1, const Circle& circle2) {
	float len = (circle1.center.x - circle2.center.x) * (circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y) * (circle1.center.y - circle2.center.y);
	return len <= (circle1.radius + circle1.radius);
}

bool GeometryOp::CircleWithRectangle(const Circle& circle, const Rectangle& rect) {
	bool a = CircleWithLine(circle, rect.point1, rect.point2);
	bool b = CircleWithLine(circle, rect.point2, rect.point3);
	bool c = CircleWithLine(circle, rect.point3, rect.point4);
	bool d = CircleWithLine(circle, rect.point4, rect.point1);
	return a || b || c || d;
}

bool GeometryOp::IsLineDiv(vectorf2 base, vectorf2 line, vectorf2 point1, vectorf2 point2, const Rectangle& rect) {

	vectorf2 mas[6];
	mas[0] = point1 - base;
	mas[1] = point2 - base;
	mas[2] = vectorf2(rect.point1.x - base.x, rect.point1.y - base.y);
	mas[3] = vectorf2(rect.point2.x - base.x, rect.point2.y - base.y);
	mas[4] = vectorf2(rect.point3.x - base.x, rect.point3.y - base.y);
	mas[5] = vectorf2(rect.point4.x - base.x, rect.point4.y - base.y);

	float mas1[6];
	for (int i = 0; i < 6; ++i) {
		mas1[i] = Cross(line, mas[i]);
	}

	bool a = (mas1[0] < 0.0f) && (mas1[1] < 0.0f);
	bool b = (mas1[2] > 0.0f) && (mas1[3] > 0.0f) && (mas1[4] > 0.0f) && (mas1[5] > 0.0f);
	bool c = (mas1[0] > 0.0f) && (mas1[1] > 0.0f);
	bool d = (mas1[2] < 0.0f) && (mas1[3] < 0.0f) && (mas1[4] < 0.0f) && (mas1[5] < 0.0f);

	return (a && b) || (c && d);
}

bool GeometryOp::RectangleWithRectangle(const Rectangle& rect1, const Rectangle& rect2) {

	bool mas[8];

	vectorf2 r1 = vectorf2(rect1.point1.x - rect1.point2.x, rect1.point1.y - rect1.point2.y);
	vectorf2 r2 = vectorf2(rect1.point2.x - rect1.point3.x, rect1.point2.y - rect1.point3.y);
	vectorf2 r3 = vectorf2(rect1.point3.x - rect1.point4.x, rect1.point3.y - rect1.point4.y);
	vectorf2 r4 = vectorf2(rect1.point4.x - rect1.point1.x, rect1.point4.y - rect1.point1.y);

	vectorf2 r5 = vectorf2(rect2.point1.x - rect2.point2.x, rect2.point1.y - rect2.point2.y);
	vectorf2 r6 = vectorf2(rect2.point2.x - rect2.point3.x, rect2.point2.y - rect2.point3.y);
	vectorf2 r7 = vectorf2(rect2.point3.x - rect2.point4.x, rect2.point3.y - rect2.point4.y);
	vectorf2 r8 = vectorf2(rect2.point4.x - rect2.point1.x, rect2.point4.y - rect2.point1.y);
	
	mas[0] = IsLineDiv(rect1.point1, r1, rect1.point3, rect1.point4, rect2);
	mas[1] = IsLineDiv(rect1.point2, r2, rect1.point1, rect1.point4, rect2);
	mas[2] = IsLineDiv(rect1.point3, r3, rect1.point1, rect1.point2, rect2);
	mas[3] = IsLineDiv(rect1.point4, r4, rect1.point2, rect1.point3, rect2);
	mas[4] = IsLineDiv(rect2.point1, r5, rect2.point3, rect2.point4, rect1);
	mas[5] = IsLineDiv(rect2.point2, r6, rect2.point1, rect2.point4, rect1);
	mas[6] = IsLineDiv(rect2.point3, r7, rect2.point1, rect2.point2, rect1);
	mas[7] = IsLineDiv(rect2.point4, r8, rect2.point2, rect2.point3, rect1);

	return !(mas[0] || mas[1] || mas[2] || mas[3] || mas[4] || mas[5] || mas[6] || mas[7]);
}

void GeometryOp::Normilize(vectorf2& vec) {
	float len = sqrt(vec.x * vec.x + vec.y * vec.y);
	vec.x /= len;
	vec.y /= len;
}

vectorf2 GeometryOp::GetDelMul(const vectorf2& dir, const vectorf2& p1, const vectorf2& p2, const vectorf2& p) {
	if ((p1.y - p2.y) == 0.0f) {
		if (dir.y == 0) {
			return vectorf2(2, 2);
		}
		float t = (p.y - p1.y) / dir.y;
		float t1 = (p.x - p1.x - dir.x * t) / (p1.x - p2.x);
		return vectorf2(t, t1);
	}
	float t = (p.x - p1.x - (p1.x - p2.x) * (p.y - p1.y) / (p1.y - p2.y)) / (dir.x - (dir.y * (p1.x - p2.x) / (p1.y - p2.y)));
	float t1 = (p.y - p1.y - dir.y * t) / (p1.y - p2.y);
	return vectorf2(t, t1);
}