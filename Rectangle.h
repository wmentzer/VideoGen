#pragma once

#include <cstdint>
using namespace std;

class Rectangle {
public:
	Rectangle(int height, int width, int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
		h = height;
		w = width;
		this->x = x;
		this->y = y;
		r = red;
		g = green;
		b = blue;
	};

	int h, w;
	uint8_t r, g, b;
	int x, y;
};
