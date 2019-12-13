#pragma once
#define brickLength 5
#include "Point.h"
#include "CDraw.h"
#include "CPong.h"
class Brick
{
private:
	Point curCor;
	int level;
	int length;
public:
	int getX();
	int getY();
	int getLevel();
	int getLength();
	void setCur(int x, int y) {
		curCor.setX(x);
		curCor.setY(y);
	}
	void setLevel(int lvl) {
		level = lvl;
	}
	bool processTouch(CPong& ball); //xử lí chạm bóng

	void draw();
	void erase();

	Brick(int, int, int);
	Brick();
	~Brick();
};

