#include "pch.h"
#include "BrickMatrix.h"
#include <random>
#include <ctime>

void BrickMatrix::initialBrickRandom()
{
	setCur(3, 10, 3);
	int x, y = 4;
	srand(time(NULL));
	for (int i = 0; i < row; i++)
	{
		x = 3;
		for (int j = 0; j < col; j++)
		{
			Mat[i][j].setCur(x, y);
			Mat[i][j].setLength(brickLength);
			x += 6;
			int a = rand() % 5 + 1;
			Mat[i][j].setLevel(a);
		}
		y += 3;
	}
}

void BrickMatrix::setCur(int r, int c, int spa) //Xét tọa độ cho từng viên gạch
{
	int x, y = 4;
	row = r;
	col = c;
	for (int i = 0; i < row; i++)
	{
		x = 3;
		for (int j = 0; j < col; j++)
		{
			Mat[i][j].setCur(x, y);
			Mat[i][j].setLength(brickLength);
			x += 6;
		}
		y += spa;
	}
}

void BrickMatrix::initLv1()
{
	setCur(3, 10, 3);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Mat[i][j].setLevel(1);
		}
	}
}

void BrickMatrix::initLv2()
{
	setCur(3, 10, 3);
	srand(time(NULL));
	int limit;
	for (int i = 0; i < row; i++)
	{
		limit = 0;
		for (int j = 0; j < col; j++)
		{
			int a = rand() % 3 + 1;
			if (a == 2)
				a = 1;
			if (a == 3)
			{
				limit++;
			}
			if (limit > 2)
			{
				a = rand() % 2 + 1;
				if (a == 2)
					a = 1;
				limit--;
			}
			Mat[i][j].setLevel(a);
		}
	}
}

void BrickMatrix::initLv3()
{
	setCur(4, 10, 3);
	srand(time(NULL));
	int limit;
	for (int i = 0; i < row; i++)
	{
		limit = 0;
		for (int j = 0; j < col; j++)
		{
			int a = rand() % 3 + 1;
			if (a == 3)
			{
				limit++;
			}
			if (limit > 1)
			{
				a = rand() % 2 + 1;
				limit--;
			}
			Mat[i][j].setLevel(a);
		}
	}
}

void BrickMatrix::initLv4()
{
	setCur(4, 10, 3);
	srand(time(NULL));
	int limit;
	for (int i = 0; i < row; i++)
	{
		limit = 0;
		for (int j = 0; j < col; j++)
		{
			if (i == row - 1 && j % 3 == 0)
			{
				Mat[i][j].setLevel(4);
				continue;
			}
			int a = rand() % 3 + 1;
			if (a == 3)
			{
				limit++;
				if (limit > 1)
				{
					while (a == 3)
					{
						a = rand() % 3 + 1;
					}
					limit--;
				}
			}
			Mat[i][j].setLevel(a);
		}
	}
}

void BrickMatrix::initLv5()
{
	setCur(4, 10, 3);
	srand(time(NULL));
	int limit;
	int bonus = 0;
	for (int i = 0; i < row; i++)
	{
		limit = 0;
		for (int j = 0; j < col; j++)
		{
			int a = rand() % 5 + 1;
			if (a == 3)
			{
				limit++;
				if (limit > 1)
				{
					while (a == 3)
					{
						a = rand() % 5 + 1;
					}
					limit--;
				}
			}
			if (a == 4)
			{
				bonus++;
				if (bonus > 6)
				{
					while (a == 3 || a == 4)
					{
						a = rand() % 5 + 1;
					}
					bonus--;
				}
			}
			Mat[i][j].setLevel(a);
		}
	}
}

void BrickMatrix::setLvlAll(int a)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Mat[i][j].getLevel() != 0)
			{
				Mat[i][j].setLevel(a);
			}
		}
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

void BrickMatrix::processTouch(CPong& Ball, int& point, vector<CBonus>& bonus)
{
	CBonus a;
	srand(time(NULL));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Mat[i][j].getLevel() == 0)	//Neu lvl cua gach = 0 thi khong xet
				continue;
			if (Mat[i][j].getY() == Ball.getCurY() + 1 || Mat[i][j].getY() == Ball.getCurY() - 1)	//Bong cham mat tren hoac mat duoi cua gach
			{
				if (Ball.getCurX() == Mat[i][j].getX() - brickLength / 2 - 1)	//Bong cham goc tren hoac goc duoi ben trai
				{
					if (Ball.getCurY() + 1 == Mat[i][j].getY())
						Ball.changDir(UPLEFT);
					else if (Ball.getCurY() - 1 == Mat[i][j].getY())
						Ball.changDir(DOWNLEFT);

					checkLevel(i, j, bonus);
					if (Mat[i][j].getLevel() != 3 && Mat[i][j].getLevel() != 4)	//Cong diem khi pha gach
						point += 100;
					Mat[i][j].afterTouch();
					Mat[i][j].draw();
					return;
				}
				for (int k = 0; k < brickLength; k++)			//Bong cham gach
				{
					if (Ball.getCurX() == Mat[i][j].getX() - brickLength / 2 + k)
					{
						if (Ball.getCurY() + 1 == Mat[i][j].getY())
							Ball.changDir((Ball.getDir() == DOWNLEFT) ? UPLEFT : UPRIGHT);
						else if (Ball.getCurY() - 1 == Mat[i][j].getY())
							Ball.changDir((Ball.getDir() == UPLEFT) ? DOWNLEFT : DOWNRIGHT);

						checkLevel(i, j, bonus);
						if (Mat[i][j].getLevel() != 3 && Mat[i][j].getLevel() != 4)
							point += 100;
						Mat[i][j].afterTouch();
						Mat[i][j].draw();
						return;
					}
				}
				if (Ball.getCurX() == Mat[i][j].getX() + brickLength / 2 + 1)	//Bong cham goc tren hoac goc duoi ben phai
				{
					if (Ball.getCurY() + 1 == Mat[i][j].getY())
						Ball.changDir(UPRIGHT);
					else if (Ball.getCurY() - 1 == Mat[i][j].getY())
						Ball.changDir(DOWNRIGHT);
					
					checkLevel(i, j, bonus);
					if (Mat[i][j].getLevel() != 3 && Mat[i][j].getLevel() != 4)
						point += 100;
					Mat[i][j].afterTouch();
					Mat[i][j].draw();
					return;
				}
			}
		}
	}
}

void BrickMatrix::checkLevel(int i, int j, vector<CBonus>& bonus)
{
	if (Mat[i][j].getLevel() == 4)
	{
		CBonus a;
		a.setType(rand() % 8 + 1);
		a.setCur(Mat[i][j].getX(), Mat[i][j].getY() + 1);
		bonus.push_back(a);
	}
}

bool BrickMatrix::win() //hàm kiểm tra xem các viên gạch đã được phá hết chưa, nếu hết trả về true
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (Mat[i][j].getLevel() != 0 && Mat[i][j].getLevel() != 3)
				return false;
		}
	return true;
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
