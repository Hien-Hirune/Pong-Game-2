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

bool Brick::processTouch(CPong& ball)
{
	//xét tung độ của bóng và gạch
	if (ball.getCurY() == curCor.getY() ||
		(ball.getCurY() == curCor.getY() - 1 && ball.getDir() == UPLEFT) ||
		(ball.getCurY() == curCor.getY() - 1 && ball.getDir() == UPRIGHT) ||
		(ball.getCurY() == curCor.getY() + 1 && ball.getDir() == DOWNLEFT) ||
		(ball.getCurY() == curCor.getY() + 1 && ball.getDir() == DOWNRIGHT))
	{ //xét hoành độ
		if (ball.getCurX() < curCor.getX() - brickLength / 2 || ball.getCurX() > curCor.getX() + brickLength / 2)
			return false;
		erase(); //xóa gạch
		level--;
		if (level >= 1) //nếu vẫn còn level
			draw(); //vẽ lại gạch với màu khác
		//xét chuyển hướng cho bóng
		if ((ball.getCurY() == curCor.getY() - 1)) //nếu bóng đang đi lên thì đổi hướng
		{
			ball.changDir((ball.getDir() == UPRIGHT) ? DOWNRIGHT : DOWNLEFT);
		}
		if ((ball.getCurY() == curCor.getY() + 1)) //nếu bóng đang đi xuống 
		{
			ball.changDir((ball.getDir() == DOWNRIGHT) ? UPRIGHT : UPLEFT);
		}
		return true;
	}
	return false;
}

void Brick::draw()
{
	gotoXY(curCor.getX(), curCor.getY());
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
	cout << "\xDC\xDC\xDC\xDC\xDC";
	setColor(0, 7);
}

void Brick::erase()
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(curCor.getX() + i, curCor.getY());
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
