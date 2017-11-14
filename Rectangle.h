#pragma once

#include <cstdint>
using namespace std;

#define W 720
#define H 480

class Rectangle {
public:
	Rectangle(int height, int width, int x, int y, uint8_t red, uint8_t green, uint8_t blue);

	int getX() { return xPos; };
	void setX(int newX) { xPos = newX; };
	void setY(int newY) { yPos = newY; };
	int getY() { return yPos; };
	int getHeight() { return h; };
	int getWidth() { return w; };
	uint8_t getRed() { return r; };
	uint8_t getGreen() { return g; };
	uint8_t getBlue() { return b; };
	void draw_rect(unsigned char frame[][W][3]) const;
	void setColor(uint8_t red, uint8_t green, uint8_t blue);

private:
	int h, w;
	uint8_t r, g, b;
	int xPos, yPos;
};
