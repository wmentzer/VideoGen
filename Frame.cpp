#include <iostream>
#include <cstdint>
#include "Frame.h"
#include "Rectangle.h"
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cstring>
#include <vector>

#define W 720
#define H 480

unsigned char frame[H][W][3];

using namespace std;

void Frame::clear_frame() {
	memset(frame, 0, sizeof(frame));
}

bool Frame::outside_frame(int * x, int * y) {
	return *x < 0 or *x >= W or *y < 0 or *y >= H;
};

void Frame::clamp(int x, int y) {
	if (x < 0) x = 0; else if (x >= W) x = W - 1;
	if (y < 0) y = 0; else if (y >= H) y = H - 1;
};

void Frame::draw_frame(double t, vector<Rectangle> rec) {
	clear_frame();
	const double pps = 80; // pixels per second
	for(int i = 0; i < rec.size(); i++) {
		int newX = rec[i].getX() + t * pps;
		int newY = rec[i].getY() + t * pps;
		rec[i].setX(newX);
		rec[i].setY(newY);
		rec[i].draw_rect(frame);
	}
};
