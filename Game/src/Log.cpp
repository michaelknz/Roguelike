#include "Log.h"

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