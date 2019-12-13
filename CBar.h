#pragma once
#include "pch.h"
#include "Point.h"
#include "CDraw.h"

#define space 3

#define KEY_UP 72
#define KEY_DOWN 80

#define playerOneLeftControl KEY_LEFT
#define playerOneRightControl KEY_RIGHT
#define barLength 13
#define WIDTH 62
#define HEIGHT 30

#define barChar '\xDB'

class CBar
{
private:
	Point curCor; // vi tri hien tai
	Point spawnCor; // vi tri xuat hien
	int length; // do dai 
public:
	void moveRight(); // di chuyen len
	void moveLeft(); // di chuyen xuong
	void move(char); // di chuyen
	void reset(); // khoi tao lai
	void initial(int,int); // khoi tao
	bool LeftCheck(); // check o tren
	bool RightCheck(); // check o duoi

	int getCurX() {
		return curCor.getX();
	}
	int getCurY() {
		return curCor.getY();
	}
	int getLength() {
		return length;
	}
	void setCur(int x,int y) {
		curCor.setX(x);
		curCor.setY(y);
	}
	CBar(int x, int y,int);
	CBar();
	~CBar();
};

