#pragma once
#include <iostream>
using namespace std;

class Point
{
	int x, y;
public:
	//lay toa do x
	int getX();
	// lay toa do y
	int getY();
	// thay doi tao do x
	void setX(int);
	// thay doi toa do y
	void setY(int);
	double distance(Point);
	Point();
	Point(int corX, int corY);
	~Point();
};

