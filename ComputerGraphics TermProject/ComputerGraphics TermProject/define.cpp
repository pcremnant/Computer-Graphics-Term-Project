#include"define.h"

GLclampf cBackground_red = 1.0f;
GLclampf cBackground_green = 1.0f;
GLclampf cBackground_blue = 1.0f;


void SetRandomColor(GLclampf& r, GLclampf& g, GLclampf& b)
{
	std::random_device rnd;
	std::mt19937 rn(rnd());
	std::uniform_real_distribution<GLclampf> range(0, 1);

	r = range(rn), g = range(rn), b = range(rn);
}