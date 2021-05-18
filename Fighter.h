#pragma once
#include "math.h"
#include "Bullet.h"

class Fighter {
public:
	Fighter(float _x, float _y, float _a) {
		x = _x;
		y = _y;
		angle = _a;

		fov = 12.5;
		radius = 20.0f;
		speed = 10.0f;

		col = sf::Color(100, 100, 50);

		movingForward = false;
		turningCW = false;
		turningCCW = false;
		firing = false;

		reloadFrames = RELOADTIME;
	}

	void update();

	float x;
	float y;

	sf::Color col;
	float speed;
	float angle;
	float radius;
	float fov;

	bool movingForward;
	bool turningCW;
	bool turningCCW;

	bool firing;
	int reloadFrames;

	const int RELOADTIME = 20;
	const float MOVESPEED = 1.5;
	const float TURNSPEED = 1.2;
	const float BULLETSPEED = 2.5;

	std::vector<Bullet*> bullets;
};