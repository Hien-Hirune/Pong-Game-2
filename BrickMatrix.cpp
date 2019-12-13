#include "pch.h"
#include "BrickMatrix.h"
#include <random>
#include <ctime>

void BrickMatrix::initialBrickRandom()
{
	int x, y = 4;
	srand(time(NULL));
	for (int i = 0; i < row; i++)
	{
		x = 3;
		for (int j = 0; j < col; j++)
		{
			Mat[i][j].setCur(x, y);
			Mat[i][j].setLength(brickLength);
			x += 5;
			int a = rand() % 3 + 1;
			Mat[i][j].setLevel(a);
		}
		y += 3;
	}
}

void BrickMatrix::drawBricks()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Mat[i][j].draw();
		}
	}
}

void BrickMatrix::processTouch(CPong& Ball,int& point)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Mat[i][j].getLevel() == 0)
			{
				continue;
			}
			if (Mat[i][j].getY() == Ball.getCurY() + 1 || Mat[i][j].getY() == Ball.getCurY() - 1)
			{
				if (Ball.getCurX() == Mat[i][j].getX() - brickLength / 2 - 1)
				{
					if (Ball.getCurY() + 1 == Mat[i][j].getY())
					{
						Ball.changDir(UPLEFT);
					}
					else if (Ball.getCurY() - 1 == Mat[i][j].getY())
					{
						Ball.changDir(DOWNLEFT);
					}
					Mat[i][j].setLevel(Mat[i][j].getLevel() - 1);
					Mat[i][j].draw();
					point += 100;
					return;
				}
				for (int k = 0; k < brickLength ; k++)
				{
					if (Ball.getCurX() == Mat[i][j].getX() - brickLength / 2 + k)
					{
						if (Ball.getCurY() + 1 == Mat[i][j].getY())
						{
							Ball.changDir((Ball.getDir() == DOWNLEFT) ? UPLEFT : UPRIGHT);
						}
						else if (Ball.getCurY() - 1 == Mat[i][j].getY())
						{
							Ball.changDir((Ball.getDir() == UPLEFT) ? DOWNLEFT : DOWNRIGHT);
						}
						Mat[i][j].setLevel(Mat[i][j].getLevel() - 1);
						Mat[i][j].draw();
						point += 100;
						return;
					}
				}
				if (Ball.getCurX() == Mat[i][j].getX() + brickLength / 2 + 1)
				{
					if (Ball.getCurY() + 1 == Mat[i][j].getY())
					{
						Ball.changDir(UPRIGHT);
					}
					else if (Ball.getCurY() - 1 == Mat[i][j].getY())
					{
						Ball.changDir(DOWNRIGHT);
					}
					Mat[i][j].setLevel(Mat[i][j].getLevel() - 1);
					Mat[i][j].draw();
					point += 100;
					return;
				}
			}
		}
	}
}

BrickMatrix::BrickMatrix(int r,int c)//(row,col)
{
	row = r;
	col = c;
}

BrickMatrix::BrickMatrix()
{
}

BrickMatrix::~BrickMatrix()
{
}
