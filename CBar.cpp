#include "pch.h"
#include "CBar.h"


// tra ve vi tri ban dau
void CBar::reset() {
	curCor.setX(spawnCor.getX());
	curCor.setY(spawnCor.getY());
}

// khoi tao 
void CBar::initial(int x,int y) {
	spawnCor.setX(x);
	spawnCor.setY(y);
	curCor = spawnCor;
	length = barLength;
}

// di len
void CBar::moveRight() {
	curCor.setX(curCor.getX() + 3);
}

// di xuong
void CBar::moveLeft() {
	curCor.setX(curCor.getX() - 3);
}

// check xem co di len duoc phia tren khong
bool CBar::LeftCheck() {
	if ((getCurX() - getLength() / 2 < 4)) {
		return false;
	}
	return true;
}
// check xem co di xuong duoi duoc khong
bool CBar::RightCheck() {
	if ((getCurX() + getLength() / 2 > WIDTH - 5)) {
		return false;
	}
	return true;
}

// di chuyen
void CBar::move(char movingKey) {
	// ham di chuyen len xuong bang cac xoa 1 thanh o huong nguoc lai va ve 1 thanh moi o huong di chuyen
		if (movingKey == playerOneLeftControl) {
			if (LeftCheck()) {
				gotoXY(getCurX() + getLength() / 2 - 2, getCurY());
				std::cout << "   ";
				moveLeft();
				gotoXY(getCurX() - getLength() / 2, getCurY());
				std::cout << barChar << barChar << barChar;
			}
		}
		else {
			if (RightCheck()) {
				gotoXY(getCurX() - getLength() / 2, getCurY());
				std::cout << "   ";
				moveRight();
				gotoXY(getCurX() + getLength() / 2 - 2, getCurY());
				std::cout << barChar << barChar << barChar;
			}
		}
}


CBar::CBar(int x, int y,int newLength)
{
	curCor.setX(x);
	curCor.setY(y);
	spawnCor.setX(x);
	spawnCor.setY(y);
	length = newLength;
}

CBar::CBar()
{
	length = 0;
}


CBar::~CBar()
{
}
