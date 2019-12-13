#include "pch.h"
#include "Brick.h"
#include <iostream>

using namespace std;

int Brick::getX()
{
	return curCor.getX();
}

int Brick::getY()
{
	return curCor.getY();
}

int Brick::getLevel()
{
	return level;
}

int Brick::getLength()
{
	return length;
}


void Brick::draw()
{
	setColor(0, 7);
	gotoXY(curCor.getX() - brickLength / 2, curCor.getY());
	if (level == 0)
	{
		setColor(0, 0);
	}
	if (level == 1)
	{
		setColor(0, 7);
	}
	if (level == 2)
	{
		setColor(0, 9);
	}
	if (level == 3)
	{
		setColor(0, 2);
	}
	cout << "\xDF\xDF\xDF\xDF\xDF";
	setColor(0, 7);
}

void Brick::erase()
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(curCor.getX() - length / 2 + i, curCor.getY());
		cout << " ";
	}
}

Brick::Brick(int x, int y, int lv)
{
	curCor.setX(x); curCor.setY(y);
	length = brickLength; level = lv;
}

Brick::Brick()
{
}

Brick::~Brick()
{
}
