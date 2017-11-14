#include <iostream>
#include "Frame.h"
#include "Rectangle.h"
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstdint>
#include <vector>

using namespace std;

int create(Frame f, vector<Rectangle> rec) {
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
	int num_frames = f.getDuration() * f.getFPS();
	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / f.getFPS();
		f.draw_frame(time_in_seconds, rec);
		fwrite(f.getArray(), 3, W * H, pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
};

int main(int argc, char * argv[]) {
	Frame f;
	Rectangle r1(10,20,0,0,0x00,0xff,0x00);
	Rectangle r2(10,20,55,55,0x00,0x00,0xff);
	Rectangle r3(10,20,44,44,0xff,0x00,0x00);
	Rectangle r4(10,20,99,99,0xff,0xff,0x00);
	vector<Rectangle> rec;
	rec.push_back(r1);
	rec.push_back(r2);
	rec.push_back(r3);
	rec.push_back(r4);
	
create(f, rec);
}
