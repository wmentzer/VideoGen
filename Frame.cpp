#pragma once

#include <iostream>
#include <cstdint>
#include "Frame.h"
#include "Rectangle.h"
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cstring>

#define W 720
#define H 480

unsigned char frame[H][W][3];

using namespace std;

void Frame::clear_frame() {
	memset(frame, 0, sizeof(frame));
}

void Frame::draw_rect(Rectangle rec1, Rectangle rec2, Rectangle rec3, Rectangle rec4) {
	if (outside_frame(&rec1.x,&rec1.y)) return;
	int rec1x0 = rec1.x;
	int rec1x1 = rec1.x + rec1.w;
	int rec1y0 = rec1.y;
	int rec1y1 = rec1.y + rec1.h;
	clamp(rec1x0, rec1y0);
	clamp(rec1x1, rec1y1);
	for (int y = rec1y0; y < rec1y1; ++y) {
		for (int x = rec1x0; x < rec1x1; ++x) {
			frame[y][x][0] = rec1.r;
			frame[y][x][1] = rec1.g;
			frame[y][x][2] = rec1.b;
		}
	}

	if (outside_frame(&rec2.x,&rec2.y)) return;
	int rec2x0 = rec2.x;
	int rec2x1 = rec2.x + rec2.w;
	int rec2y0 = rec2.y;
	int rec2y1 = rec2.y + rec2.h;
	clamp(rec2x0, rec2y0);
	clamp(rec2x1, rec2y1);
	for (int y = rec2y0; y < rec2y1; ++y) {
		for (int x = rec2x0; x < rec2x1; ++x) {
			frame[y][x][0] = rec2.r;
			frame[y][x][1] = rec2.g;
			frame[y][x][2] = rec2.b;
		}
	}

	if (outside_frame(&rec3.x,&rec3.y)) return;
	int rec3x0 = rec3.x;
	int rec3x1 = rec3.x + rec3.w;
	int rec3y0 = rec3.y;
	int rec3y1 = rec3.y + rec3.h;
	clamp(rec3x0, rec3y0);
	clamp(rec3x1, rec3y1);
	for (int y = rec3y0; y < rec3y1; ++y) {
		for (int x = rec3x0; x < rec3x1; ++x) {
			frame[y][x][0] = rec3.r;
			frame[y][x][1] = rec3.g;
			frame[y][x][2] = rec3.b;
		}
	}

	if (outside_frame(&rec4.x,&rec4.y)) return;
	int rec4x0 = rec4.x;
	int rec4x1 = rec4.x + rec4.w;
	int rec4y0 = rec4.y;
	int rec4y1 = rec4.y + rec4.h;
	clamp(rec4x0, rec4y0);
	clamp(rec4x1, rec4y1);
	for (int y = rec4y0; y < rec4y1; ++y) {
		for (int x = rec4x0; x < rec4x1; ++x) {
			frame[y][x][0] = rec4.r;
			frame[y][x][1] = rec4.g;
			frame[y][x][2] = rec4.b;
		}
	}
};

bool Frame::outside_frame(int * x, int * y) {
	return *x < 0 or *x >= W or *y < 0 or *y >= H;
};

void Frame::clamp(int x, int y) {
	if (x < 0) x = 0; else if (x >= W) x = W - 1;
	if (y < 0) y = 0; else if (y >= H) y = H - 1;
};

void Frame::draw_frame(double t, Rectangle rec1, Rectangle rec2, Rectangle rec3, Rectangle rec4) {
	clear_frame();
	const double pps = 80; // pixels per second
	Rectangle newRec1 = rec1;
	newRec1.x = rec1.x + t * pps;
	newRec1.y = rec1.y + t * pps;

	Rectangle newRec2 = rec2;
	newRec2.x = rec2.x - t * pps;
	newRec2.y = rec2.y + t * pps;

	Rectangle newRec3 = rec3;
	newRec3.x = rec3.x + t * pps;
	newRec3.y = rec3.y - t * pps;

	Rectangle newRec4 = rec4;
	newRec4.x = rec4.x - t * pps;
	newRec4.y = rec4.y - t * pps;

	draw_rect(newRec1, newRec2, newRec3, newRec4);
};

int Frame::create(Frame x, Rectangle rec1, Rectangle rec2, Rectangle rec3, Rectangle rec4) {
	// Construct the ffmpeg command to run.
	const char * cmd =
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

	// Run the ffmpeg command and get pipe to write into its standard input stream.
	FILE * pipe = popen(cmd, "w");
	if (pipe == 0) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}

	// Write video frames into the pipe.
	int num_frames = x.duration_in_seconds * x.frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / x.frames_per_second;
		draw_frame(time_in_seconds, rec1, rec2, rec3, rec4);
		fwrite(frame, 3, W * H, pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}
