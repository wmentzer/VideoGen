#pragma once

#include "Rectangle.h"
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cstring>

#define W 720
#define H 480

class Frame {
public:
	Frame() {};
	~Frame() {};
	void clear_frame();
	void draw_frame(double t, Rectangle rec1, Rectangle rec2, Rectangle rec3, Rectangle rec4);
	void draw_rect(Rectangle rec1, Rectangle rec2, Rectangle rec3, Rectangle rec4);
	bool outside_frame(int * x, int * y);
	void clamp(int x, int y);
	int create(Frame f, Rectangle rec1, Rectangle rec2, Rectangle rec3, Rectangle rec4);

private:
	const double frames_per_second = 30; 
	const int duration_in_seconds = 5;

	unsigned char frame[H][W][3];

	friend class Rectangle;
};

