#include "Rectangle.h"
#include <cstdint>

#define W 720
#define H 480

Rectangle::Rectangle(int height, int width, int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
	h = height;
	w = width;
	xPos = x;
	yPos = y;
	r = red;
	g = green;
	b = blue;
};

void Rectangle::draw_rect(unsigned char frame[][W][3]) const {
	int x0 = xPos;
	int x1 = xPos + w;
	int y0 = yPos;
	int y1 = yPos + h;

	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
};

void Rectangle::setColor(uint8_t red, uint8_t green, uint8_t blue) {
	r = red;
	g = green;
	b = blue;
};
