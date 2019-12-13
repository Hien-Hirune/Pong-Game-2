#include "pch.h"
#include "CPong.h"

#define WIDTH 62
#define HEIGHT 30

// tra ve vi tri ban dau
void CPong::reset() {
	curCor.setX(WIDTH/2-1);
	curCor.setY(HEIGHT/2-1);
	direction = STOP;
}

// doi huong di chuyen
void CPong::changDir(dir newDir)
{
	direction = newDir;
}

// khoi tao
void CPong::initial() {
	spawnCor.setX(WIDTH / 2 - 1);
	spawnCor.setY(HEIGHT / 2 - 1);
	curCor = spawnCor;
}

// di chuyen
void CPong::Move()
{
	// cong tru toa do theo huong
	switch (direction) {
	case STOP:
		break;
	case UP:
		curCor.setY(curCor.getY() - 1);
		break;
	case DOWN:
		curCor.setY(curCor.getY() + 1);
		break;
	case UPLEFT:
		curCor.setX(curCor.getX() - 1);
		curCor.setY(curCor.getY() - 1);
		break;
	case DOWNLEFT:
		curCor.setX(curCor.getX() - 1);
		curCor.setY(curCor.getY() + 1);
		break;
	case UPRIGHT:
		curCor.setX(curCor.getX() + 1);
		curCor.setY(curCor.getY() - 1);
		break;
	case DOWNRIGHT:
		curCor.setX(curCor.getX() + 1);
		curCor.setY(curCor.getY() + 1);
		break;
	}
}

// ve banh tai diem xuat hien
void CPong::draw(char c)
{
	gotoXY(curCor.getX(), curCor.getY());
	std::cout << c;
}



CPong::CPong() {
	direction = STOP;
	curCor.setX(WIDTH / 2);
	curCor.setY(HEIGHT / 2);
}

CPong::CPong(int x,int y)
{
	curCor.setX(x);
	curCor.setY(y);
	spawnCor.setX(x);
	spawnCor.setY(y);
	direction = STOP;
}


CPong::~CPong()
{
}
