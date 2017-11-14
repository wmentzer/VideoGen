#pragma once

#include "Rectangle.h"
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cstring>
#include <vector>

#define W 720
#define H 480

class Frame {
public:
	Frame() {};
	~Frame() {};
	void clear_frame();
	void draw_frame(double t, vector<Rectangle> rec);
	bool outside_frame(int * x, int * y);
	void clamp(int x, int y);
	double getFPS() { return frames_per_second; };
	int getDuration() {return duration_in_seconds; };
	unsigned char* getArray() { return (unsigned char*) frame; };

private:
	const double frames_per_second = 30;
	const int duration_in_seconds = 4;

	unsigned char frame[H][W][3];
};

