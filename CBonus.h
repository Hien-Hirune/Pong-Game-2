#pragma once
#include "Point.h"
#include "CDraw.h"

class CBonus
{
private:
	Point curCor;
	int Type;
public:
	int getX() {
		return curCor.getX();
	}
	int getY() {
		return curCor.getY();
	}
	void setCur(int x, int y)
	{
		curCor.setX(x);
		curCor.setY(y);
	}
	int getType()
	{
		return Type;
	}
	void setType(int t)
	{
		Type = t;
	}
	void draw(char);
	CBonus();
	~CBonus();
};

