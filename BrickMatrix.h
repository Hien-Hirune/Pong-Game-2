#pragma once
#include "Brick.h"

#define MAX 20

class BrickMatrix
{
private:
	Brick Mat[MAX][MAX];
	int col;
	int row;
public:
	void initialBrickRandom(); //khởi tạo bricks
	void drawBricks();
	int getCol()
	{
		return col;
	}
	int getRow()
	{
		return row;
	}
	void setRow(int r)
	{
		row = r;
	}
	void setCol(int c)
	{
		col = c;
	}
	Brick getBrick(int r, int c)
	{
		return Mat[r][c];
	}
	void processTouch(CPong& Ball, int&);
	BrickMatrix(int, int);
	BrickMatrix();
	~BrickMatrix();
};

