#pragma once
#include "pch.h"
#include "Point.h"
#include "CDraw.h"
#include <time.h>
#include <random>

#define pongChar 'O'
#define delChar ' '
enum dir {STOP = 0, UP = 1, UPLEFT = 2, UPRIGHT = 3, DOWN = 4, DOWNLEFT = 5, DOWNRIGHT = 6};

class CPong
{
private:
	Point curCor;
	Point spawnCor;
	enum dir direction;

public:
	void reset(); // khoi tao vi tri ban dau
	void changDir(dir newDir); // thay doi huong di cua banh
	void Move(); // banh di chuyen
	void initial(); // khoi tao
	void randomDir() { // tao 1 huong ngau nhien
		direction = (dir)((rand() % 6 + 1));
	}

	void draw(char c); // ve banh

	int getCurX() {
		return curCor.getX();
	}
	int getCurY() {
		return curCor.getY();
	}
	dir getDir() {
		return direction;
	}
	void setCur(int x, int y) {
		curCor.setX(x);
		curCor.setY(y);
	}
	void setDir(int past) {
		direction = dir(past);
	}
	CPong();
	CPong(int x, int y);
	~CPong();
};

