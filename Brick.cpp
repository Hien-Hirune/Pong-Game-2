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


void Brick::draw()		// Ve gach
{
	setColor(0, 7);
	gotoXY(curCor.getX() - brickLength / 2, curCor.getY());
	if (level == 0)
	{
		setColor(0, 0);		// Mau den
	}
	if (level == 1)
	{
		setColor(0, 7);		// Mau trang
	}
	if (level == 2)
	{
		setColor(0, 2);		//Mau xanh la
	}
	if (level == 3)
	{
		setColor(0, 4);		//Mau do
	}
	if (level == 4)
	{
		setColor(0, 6);		// Mau vang cam
	}
	if (level == 5)			// Mau xanh duong
	{
		setColor(0, 1);
	}
	cout << "\xDF\xDF\xDF\xDF\xDF";
	setColor(0, 7);
}

void Brick::erase()		//Xoa gach
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(curCor.getX() - length / 2 + i, curCor.getY());
		cout << " ";
	}
}
	
void Brick::afterTouch()	// Doi loai gach sau va cham
{
	if (level == 1)
	{
		level = 0;
		return;
	}
	else if (level == 2)
	{
		level = 1;
		return;
	}
	else if (level == 3)
	{
		return;
	}
	else if (level == 4)
	{
		level = 0;
		return;
	}
	else if (level == 5)
	{
		level = 2;
		return;
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
