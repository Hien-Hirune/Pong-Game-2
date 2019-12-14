#include "pch.h"
#include "Point.h"

// tinh khoang cach tu 1 diem toi diem con lai
double Point::distance(Point b) {
	double disX = x - b.getX();
	double disY = y - b.getY();
	return sqrt(disX*disX + disY * disY);
}

int Point::getX() {
	return x;
}
int Point::getY() {
	return y;
}

void Point::setX(int newX) {
	x = newX;
}
void Point::setY(int newY) {
	y = newY;
}

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(int corX,int corY)
{
	x = corX;
	y = corY;
}


Point::~Point()
{
}
