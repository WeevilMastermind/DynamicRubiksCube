#pragma once
#include <iostream>
#include "slice.h"
#include "cube.h"

std::string getColor(char c)//returns color string for corresponding character input
{
	switch (c)
	{
	case('F'):
		return ("\033[38;2;0;255;0m");
		break;
	case('B'):
		return ("\033[38;2;0;0;255m");
		break;
	case('U'):
		return ("\033[38;2;255;255;255m");
		break;
	case('D'):
		return ("\033[38;2;255;230;0m");
		break;
	case('L'):
		return ("\033[38;2;255;130;0m");
		break;
	case('R'):
		return ("\033[38;2;255;0;0m");
		break;
	default:
		return ("\033[38;2;255;255;255m");
	}
}

void printCube(Cube c)//prints cube faces in color
{

	std::cout << "\n\n";

			for(int i = 0; i < c.size; i++)
			{
				for (int j = 0; j < c.size * 2; j++)
				{
					if (j / c.size == 0)
						std::cout << "  ";
					else
						std::cout << getColor(c.faces[1][c.size - 1 - (j % c.size)][i])
						<< c.faces[1][c.size - 1 - (j % c.size)][i] << " ";
				}
				std::cout << "\n";
			}

		 //row 2
			for (int i = 0; i < c.size; i++)
			{
				for (int j = 0; j < c.size*4; j++)//controls end line for proper printing
				{
					switch (j / c.size)
					{
					case(0):
						std::cout << getColor(c.faces[5][c.size - 1 - j][i])
							<< c.faces[5][c.size - 1 - j][i] << " ";
						break;
					case(2):
						std::cout << getColor(c.faces[2][c.size - 1 - (j % c.size)][i])
							<< c.faces[2][c.size - 1 - (j % c.size)][i] << " ";
						break;
					case(1):
						std::cout << getColor(c.faces[0][i][j % c.size])
							<< c.faces[0][i][j % c.size] << " ";
						break;
					case(3):
						std::cout << getColor(c.faces[3][c.size - 1 - i][c.size - 1 - (j % c.size)])
							<< c.faces[3][c.size - 1 - i][c.size - 1 - (j % c.size)] << " ";
						break;
					}
				}
				std::cout << "\n";
			}

			for (int i = 0; i < c.size; i++)
			{
				for (int j = 0; j < c.size * 2; j++)
				{
					if (j / c.size == 0)
						std::cout << "  ";
					else
						std::cout << getColor(c.faces[4][j % c.size][c.size - 1 - i])
						<< c.faces[4][j % c.size][c.size - 1 - i] << " ";
				}
				std::cout << "\n";
			}

	
}

void moveSlice(int size, Slice * s, bool cw)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < size; j++)
		{ 
			char temp = *s->sides[(cw ? (i) : (3 - i))][j];
			*s->sides[(cw ? (i) : (3 - i))][j]  = *s->sides[(cw ? (i + 1) : (3 - i - 1))][j];
			*s->sides[(cw ? (i + 1) : (3 - i - 1))][j] = temp;
		}
	}
}

void moveFace(char**f, int size, bool dir)
{
	int lazy = 1;
	if (dir) lazy = 3;
	for(int direction = 0; direction < lazy; direction++)
	{
		for (int i = 0; i < size / 2; i = i + 1)
		{
			for (int j = i; j < size - i - 1; j = j + 1)
			{
				int temp = f[i][j];
				f[i][j] = f[j][size - 1 - i];
				f[j][size - 1 - i] = f[size - 1 - i][size - 1 - j];
				f[size - 1 - i][size - 1 - j] = f[size - 1 - j][i];
				f[size - 1 - j][i] = temp;
			}
		}
	}
}

void scramble(Cube c)
{
	srand(0);
	for (int i = 0; i < 10*c.size; i++)
	{
		//moveSlice(c.size, );
	}
}

void moveHandling(Cube c, std::string in, bool cw)
{
	switch (in[0])//chooses which face/slice to rotate based on the first character of 'in' string
	{
	case('f'):
		moveFace(c.faces[0], c.size, cw);
		moveSlice(c.size, c.sliceSets[1][c.size - 1], !cw);
		break;
	case('r'):
		moveFace(c.faces[2], c.size, cw);
		moveSlice(c.size, c.sliceSets[2][c.size - 1], !cw);
		break;
	case('b'):
		moveFace(c.faces[3], c.size, cw);
		moveSlice(c.size, c.sliceSets[1][0], cw);
		break;
	case('l'):
		moveFace(c.faces[5], c.size, cw);
		moveSlice(c.size, c.sliceSets[2][0], cw);
		break;
	case('u'):
		moveFace(c.faces[1], c.size, cw);
		moveSlice(c.size, c.sliceSets[0][0], cw);
		break;
	case('d'):
		moveFace(c.faces[4], c.size, cw);
		moveSlice(c.size, c.sliceSets[0][c.size - 1], !cw);
		break;
	}
}

void play()
{
	int size = 1 ;
	std::cout << "Size: ";
	std::cin >> size;
	Cube c(size);
	//scramble(c);
	//c.faces[0]->f[0][0] = '*';
	/*moveFace(c.faces[4], size, 1);
	printCube(c);*/

	std::string in;//user input
	while (in[0] != 'q')
	{
		
		system("CLS");//clear terminal

		printCube(c);//print cube
		
		std::cout << "\n\n\nInput: ";//prompt
		std::cin >> in;//collect user input


		bool cw = true;//clockwise rotation == true, counterclockwise rotation == false
		if (in.size() > 1)
			cw = false;

		moveHandling(c, in, cw);
	}
}