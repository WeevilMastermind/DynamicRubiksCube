#include "slice.h"

Slice::Slice(int _size)
	:size(_size)
{

	sides = new char** [4];
	for (int i = 0; i < 4; i++)
	{
		sides[i] = new char* [size];
		for (int j = 0; j < size; j++)
		{
			sides[i][j] = nullptr;
		}
	}
}

Slice::~Slice()
{
	for (int i = 0; i < 4; i++)
	{
		delete[] sides[i];
	}
	delete[] sides;
}