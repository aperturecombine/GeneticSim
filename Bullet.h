#pragma once
#include "math.h"

class Bullet {
public:
	Bullet(float _x, float _y, float _vx, float _vy) : 
		x(_x), y(_y), vx(_vx), vy(_vy), del(false) {}

	~Bullet() { /*std::cout << "delete!" << std::endl;*/ }

	void update() {
		x += vx;
		y += vy;

		if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) {
			del = true;
		}
	}

	float x;
	float y;
	float vx;
	float vy;

	bool del;
};