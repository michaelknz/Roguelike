#include "Log.h"
#include "RectCollider.h"
#include "Renderer.h"
#include <algorithm>

Log::Log(){

}

Log::~Log() {

}

void Log::Print(const matf4x4& val) {
	std::cout << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << val.mas[i * 4 + j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Log::Print(const vectorf2& val) {
	std::cout << std::endl;
	std::cout << '(' << val.x << ", " << val.y << ')' << std::endl;
	std::cout << std::endl;
}

void Log::Print(const vectori2& val) {
	std::cout << std::endl;
	std::cout << '(' << val.x << ", " << val.y << ')' << std::endl;
	std::cout << std::endl;
}

void Log::Print(const vectorf3& val) {
	std::cout << std::endl;
	std::cout << '(' << val.x << ", " << val.y << ", " << val.z << ')' << std::endl;
	std::cout << std::endl;
}

void Log::Print(const std::string& str) {
	std::cout << std::endl;
	std::cout << str << std::endl;
	std::cout << std::endl;
}

void Log::VisCollider(Collider* collider, Camera* cam) {
	if (collider->GetType() == RECTANGLE) {
		Rectangle rect = dynamic_cast<RectCollider*>(collider)->GetShape();
		TransformQuad tr;
		vectorf2 ul = rect.point1;
		vectorf2 dr = rect.point1;
		vectorf2 mas[4] = { rect.point1, rect.point2, rect.point3, rect.point4 };
		for (int i = 1; i < 4; ++i) {
			ul.x = fminf(ul.x, mas[i].x);
			ul.y = fmaxf(ul.y, mas[i].y);
			dr.x = fmaxf(dr.x, mas[i].x);
			dr.y = fminf(dr.y, mas[i].y);
		}
		tr.pos = vectorf2(ul.x + 0.5f * (dr.x - ul.x), dr.y + 0.5f * (ul.y - dr.y));
		tr.size = vectorf2(dr.x - ul.x, ul.y - dr.y);
		tr.is_gs = true;
		tr.z = -0.02f;
		tr.shader_name = "LogShaderRect";
		Renderer* rend = new Renderer(tr, cam);
		rend->Draw(Transform(tr.pos));
		delete rend;
	}
}