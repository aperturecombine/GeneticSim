#include "Fighter.h"

void Fighter::update() {
	float vx = cos(angle * M_PI / 180.0);
	float vy = sin(angle * M_PI / 180.0);

	if (this->movingForward) {
		this->x += vx * MOVESPEED;
		this->y += vy * MOVESPEED;
	}
	if (this->turningCW) angle -= TURNSPEED;
	if (this->turningCCW) angle += TURNSPEED;

	if (this->firing) {
		if (reloadFrames == 0) {
			reloadFrames = RELOADTIME;

			bullets.push_back(new Bullet(x + 1.5*vx*radius,
										 y + 1.5*vy*radius,
										 vx*BULLETSPEED, vy*BULLETSPEED));
		}
	}
	//std::cout << "reloadFrames: " << reloadFrames << std::endl;
	if (reloadFrames > 0) reloadFrames--;
}