#pragma once
#include "pch.h"


class Point
{
	int x, y;
public:
	int getX();
	int getY();
	void setX(int newX) {
		x = newX;
	}
	void setY(int newY) {
		y = newY;
	}
	double distance(Point);
	Point();
	Point(int corX,int corY);
	~Point();
};

