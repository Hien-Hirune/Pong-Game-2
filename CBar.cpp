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
	curCor.setX(curCor.getX() + 6);
}

// di xuong
void CBar::moveLeft() {
	curCor.setX(curCor.getX() - 6);
}

// check xem co di qua trai duoc khong
bool CBar::LeftCheck() {
	if ((getCurX() - getLength() / 2 <= 5)) {
		return false;
	}
	return true;
}
// check xem co di qua phai duoc khong
bool CBar::RightCheck() {
	if ((getCurX() + getLength() / 2 >= WIDTH - 6)) {
		return false;
	}
	return true;
}

// di chuyen
void CBar::move(char movingKey) {
	// ham di chuyen len xuong bang cac xoa 1 thanh o huong nguoc lai va ve 1 thanh moi o huong di chuyen
		if (movingKey == playerOneLeftControl) {
			if (LeftCheck()) {
				gotoXY(getCurX() + getLength() / 2 - 5, getCurY());
				std::cout << "      ";
				moveLeft();
				gotoXY(getCurX() - getLength() / 2, getCurY());
				std::cout << barChar << barChar << barChar << barChar << barChar << barChar;
			}
		}
		else {
			if (RightCheck()) {
				gotoXY(getCurX() - getLength() / 2, getCurY());
				std::cout << "      ";
				moveRight();
				gotoXY(getCurX() + getLength() / 2 - 5, getCurY());
				std::cout << barChar << barChar << barChar << barChar << barChar << barChar;
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
