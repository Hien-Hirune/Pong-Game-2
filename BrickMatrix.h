#pragma once
#include "Brick.h"
#include "CBonus.h"
#include <vector>
#define MAX 20

class BrickMatrix
{
private:
	Brick Mat[MAX][MAX];
	int col;
	int row;
public:
	void initialBrickRandom(); //khởi tạo bricks random voi 3 hang 10 cot khoang cach 3
	void setCur(int, int, int);
	void initLv1();			//lv1
	void initLv2();			//lv2
	void initLv3();			//lv3
	void initLv4();			//lv4
	void initLv5();			//lv5
	void setLvlAll(int);	//Doi tat gach cung 1 loai
	void drawBricks();		//Ve ma tran gach
	int getCol()
	{
		return col;
	}
	int getRow()
	{
		return row;
	}
	void setRow(int r)
	{
		row = r;
	}
	void setCol(int c)
	{
		col = c;
	}
	Brick getBrick(int r, int c)
	{
		return Mat[r][c];
	}
	void processTouch(CPong& Ball, int&, vector<CBonus>&);		//Xet va cham
	void checkLevel(int i, int j, vector<CBonus>& bonus);		//Kiem tra bonus
	BrickMatrix(int, int);
	BrickMatrix();
	~BrickMatrix();
};

