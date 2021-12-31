#include "Random.h"

float Random::Range(float a, float b)
{
	static std::random_device dev;
	static std::mt19937 rng(dev());
	static std::uniform_real_distribution<> dis(a, b);
	return dis(rng);
}
