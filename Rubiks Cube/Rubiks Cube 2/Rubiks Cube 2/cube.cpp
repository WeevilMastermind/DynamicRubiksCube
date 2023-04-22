#include <iostream>
#include "slice.h"
#include "cube.h"


Cube::Cube(int _size) : size(_size)
{
	//dynamically create faces
	for (int i = 0; i < 6; i++)
	{
		faces[i] = new char*[size];//delet

		for (int j = 0; j < size; j++)
		{
			faces[i][j] = new char[size];//delet
			for (int p = 0; p < size; p++)
			{
				faces[i][j][p] = faceCharacters[i];
			}
		}
	}

	for (int i = 0; i < 3; i++)//initializes sliceSets array dynamically
	{
		sliceSets[i] = new Slice*[size];
		for (int j = 0; j < size; j++)
		{
			sliceSets[i][j] = new Slice(size);
		}
	}

	/*
	
		Allocates slice sides (has 4 sides for each loop around cube) with corresponding face array side

			-The 'x' in the corner is position (0,0) on each corresponding face array.  Arrow points to "top" of array for better visualization.
			-The first dimension of sliceSets corresponds to each axis of the cube.
			-Numbers on the left of the face diagrams correspond to a position in sliceSets 2nd dimension, which points to a slice instance.
			-The Slice instance has to point to the corresponding side of the face array shown in the diagram
				-This orientation for the faces was chosen to make the construction of the slice sets less complicated
			

	  - - - - - - 	 - - - - - - 	- - - - - -    - - - - - - 
	0|x          | 0|          x| 0|           | 0|          x|
	1|   ^       | 1|     ->    | 1|        |  | 1|     ->    |
	2|   | 0     | 2|     1     | 2|     2  V  | 2|     3     |
	3|           | 3|           | 3|          x| 3|           |
	  - - - - - - 	 - - - - - - 	- - - - - -    - - - - - - 
	
	
	*/


	int sliceOffsetArr[12] = {0,2,3,5,  2,4,5,1,  4,0,1,3};//every position/4 corresponds to a slice set position, and contains each sides[4] array.
	for(int sliceSet = 0; sliceSet < 3; sliceSet++)
	{
		for (int i = 0; i < size; i++)
		{
			for(int face = 0; face < 4; face++)
			{
				for (int j = 0; j < size; j++)
				{
					switch (face)
					{
					case(0):
						sliceSets[sliceSet][i]->sides[face][j] = &faces[sliceOffsetArr[sliceSet * 4 + face]][i][j];//first edge in slice
						break;
					case(1):
						sliceSets[sliceSet][i]->sides[face][j] = &faces[sliceOffsetArr[sliceSet * 4 + face]][size - 1 - j][i];//second edge in slice
						break;
					case(2):
						sliceSets[sliceSet][i]->sides[face][j] = &faces[sliceOffsetArr[sliceSet * 4 + face]][size - 1 - i][size - 1 - j];//third edge in slice
						break;
					case(3):
						sliceSets[sliceSet][i]->sides[face][j] = &faces[sliceOffsetArr[sliceSet * 4 + face]][size - 1 - j][i];//fourth edge in slice
						break;
					default:
						std::cout << "ERROR: CUBE CONSTRUCTOR";
					}
				}
			}
		}
	}
}

//Cube::~Cube()//cube destructor
//{
//	for (int i = 0; i < 3; i++)//deletes slice sets and contained slices
//	{
//		for (int j = 0; j < size; j++)
//		{
//			delete sliceSets[i][j];
//		}
//		delete [] sliceSets[i];
//	}
//
//	for (int i = 0; i < 6; i++)//deletes face character arrays
//	{
//		for (int j = 0; j < size; j++)
//		{
//			delete faces[i][j];
//		}
//		delete[] faces[i];
//	}
//}