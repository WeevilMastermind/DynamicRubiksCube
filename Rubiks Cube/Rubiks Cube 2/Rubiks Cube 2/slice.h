#pragma once

class Slice
{
	public:
		int size = 1;
		char *** sides;//0 is (x,y) axis, 1 is (y,z) axis, 2 is (x,z) axis.  Storage order in sliceOffsetArr in cube.cpp
		Slice(int _size);
		~Slice();
};