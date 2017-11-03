#include <iostream>
#include "Frame.h"
#include "Rectangle.h"
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstdint>

using namespace std;

int main(int argc, char * argv[]) {
	Frame f;
	Rectangle r1(10,20,0,0,0x00,0xff,0x00);
	Rectangle r2(10,20,11,11,0x00,0x00,0xff);
	Rectangle r3(10,20,22,22,0xff,0x00,0x00);
	Rectangle r4(10,20,33,33,0xff,0xff,0x00);
	f.create(f,r1, r2, r3, r4);
}
