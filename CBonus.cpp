#include "pch.h"
#include "CBonus.h"

void CBonus::draw(char c)	//Ve bonus
{
	gotoXY(getX(), getY());
	setColor(0, 7);
	cout << c;
}

CBonus::CBonus()
{
}

CBonus::~CBonus()
{
}