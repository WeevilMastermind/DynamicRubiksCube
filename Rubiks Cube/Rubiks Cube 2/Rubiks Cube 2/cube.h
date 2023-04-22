#pragma once

class Cube
{
	public:
		int size;//number of tiles on each edge
		char **faces[6];//stores a face class instance for each side of the cube.  Face order corresponds to characters initialized in faceCharacters below
		char faceCharacters[6] = { 'F','U','R','B','D','L' };//characters for each face.  ORDER IS IMPORTANT
		Slice **sliceSets[3];
		Cube(int _size = 1);//constructor prototype
		//~Cube();
};