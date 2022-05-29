#ifndef LOG_H
#define LOG_H

#include <iostream>
#include "Math.h"

class Collider;
class Camera;

class Log {
public:
	Log();
	~Log();
	static void Print(const matf4x4& val);
	static void Print(const vectorf2& val);
	static void Print(const vectori2& val);
	static void Print(const vectorf3& val);
	static void Print(const std::string& str);
	static void VisCollider(Collider* collider, Camera* cam);
};

#endif