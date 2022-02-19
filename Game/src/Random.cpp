#include "Random.h"
#include <cstdlib>
#include <ctime>

Random::Random() {

}

Random::~Random() {

}

int Random::GetRandomInt(int a, int b) {
	srand(time(0));
	return rand() % (b - a + 1) + a;
}