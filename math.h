#pragma once
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Matrix.h"

#define M_PI 3.14159265

const int WIDTH = 800;
const int HEIGHT = 800;

static float getRandom() {
	return 1.0 * rand() / RAND_MAX;
}

static bool lineCircle(float x1, float y1, float x2, float y2,
						float cx, float cy, float r) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	float fx = x1 - cx;
	float fy = y1 - cy;

	float a = dx * dx + dy * dy;
	float b = 2 * (dx * fx + dy * fy);
	float c = (fx * fx + fy * fy) - r * r;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return false;
	}
	else {
		discriminant = sqrt(discriminant);
		float t1 = (-b - discriminant) / (2 * a);
		float t2 = (-b + discriminant) / (2 * a);

		if (t1 >= 0 && t1 <= 1) {
			return true;
		}
		if (t2 >= 0 && t2 <= 1) {
			return true;
		}
		return false;
	}
}

static float sign(float cx, float cy, float p2x, float p2y, float p3x, float p3y) {
	return (cx - p3x) * (p2y - p3y) - (p2x - p3x) * (cy - p3y);
}

static bool circleTriangle(float v1x, float v1y,
		float v2x, float v2y,
		float v3x, float v3y,
		float centerx, float centery, float radius) {

	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(centerx, centery, v1x, v1y, v2x, v2y);
	d2 = sign(centerx, centery, v2x, v2y, v3x, v3y);
	d3 = sign(centerx, centery, v3x, v3y, v1x, v1y);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);


	/*float c1x = v1x - centerx;
	float c1y = v1y - centery;

	if (sqrt(c1x * c1x + c1y * c1y) <= radius)
		return true;

	float c2x = v2x - centerx;
	float c2y = v2y - centery;

	if (sqrt(c2x * c2x + c2y * c2y) <= radius)
		return true;

	float c3x = v3x - centerx;
	float c3y = v3y - centery;

	if (sqrt(c3x * c3x + c3y * c3y) <= radius)
		return true;

	return false;
	*/

	/*float radiusSq = radius * radius;

	float c1x = cx - v1x;
	float c1y = cy - v1y;
	std::cout << cx << " " << cy << " " << c1x << " " << c1y << std::endl;
	float c1sqr = c1x * c1x + c1y * c1y - radiusSq;
	std::cout << c1sqr << std::endl;
	if (c1sqr <= 0) { std::cout << "1" << std::endl; return true; }

	float c2x = cx - v2x;
	float c2y = cy - v2y;
	float c2sqr = c2x * c2x + c2y * c2y - radiusSq;
	std::cout << c2x << " " << c2y << std::endl;
	std::cout << c2sqr << std::endl;
	if (c2sqr <= 0) { std::cout << "2" << std::endl; return true; }

	float c3x = cx - v3x;
	float c3y = cy - v3y;
	float c3sqr = c3x * c3x + c3y * c3y - radiusSq;
	std::cout << c3x << " " << c3y << std::endl;
	std::cout << c3sqr << std::endl;
	if (c3sqr <= 0) { std::cout << "3" << std::endl; return true; }
	std::cout << std::endl;

	return false;


	float e1x = v2x - v1x;
	float e1y = v2y - v1y;
	
	float e2x = v3x - v2x;
	float e2y = v3y - v2y;

	float e3x = v1x - v3x;
	float e3y = v1y - v3y;

	if (signed((e1y * c1x - e1x * c1y) ||
				(e2y * c2x - e2x * c2y) ||
				(e3y * c3x - e3x * c3y)) >= 0) {
		return true;
	}

	float k = c1x * e1x + c1y * e1y;
	float len;
	if (k > 0) {
		len = e1x * e1x + e1y * e1y;
		if(k < len) {
			if (c1sqr * len <= k * k) return true;
		}
	}

	k = c2x * e2x + c2y * e2y;

	if(k > 0) {
		len = e2x * e2x + e2y * e2y;
		if(k < len) {
			if(c2sqr* len <= k * k) return true;
		}
	}

	k = c3x * e3x + c3y * e3y;

	if(k > 0) {
		len = e3x * e3x + e3y * e3y;
		if(k < len) {
			if (c3sqr * len <= k * k) return true;
		}
	}

	return false;*/
}