#include "pch.h"
#include "CListBonus.h"

#define bColor 4	
#define	fontColor 7		

void CListBonus::addBonus(CBonus a)	//Them bonus
{
	List.push_back(a);
}

void CListBonus::Erase()	//Xoa bonus khoi man hinh
{
	for (int i = 0; i < List.size(); i++)
	{
		List[i].draw(' ');
	}
}

void CListBonus::Move()	//Di chuyen cac bonus
{
	for (int i = 0; i < List.size(); i++)
	{
		List[i].setCur(List[i].getX(), List[i].getY() + 1);
	}
}

void CListBonus::Delete(int i)	//Xoa bonus khoi list
{
	List.erase(List.begin() + i);
}

void CListBonus::draw()	//Ve tat ca cac bonus
{
	for (int i = 0; i < List.size(); i++)
	{
		gotoXY(List[i].getX(), List[i].getY());
		switch (List[i].getType())		//Xet theo loai bonus de ve
		{
		case 1:
			cout << "2";
			break;
		case 2:
			cout << "5";
			break;
		case 3:
			cout << "/";
			break;
		case 4:
			cout << "0";
			break;
		case 5:
			cout << "1";
			break;
		case 6:
			cout << "3";
			break;
		case 7:
			cout << "U";
			break;
		case 8:
			cout << "D";
			break;
		default:
			break;
		}
	}
}

void CListBonus::logic(CBar& bar, int& score, BrickMatrix& mat, int& speed)	//Xet va cham cho bonus voi thanh truot
{
	for (int i = 0; i < List.size(); i++)
	{
		if (List[i].getY() + 1 == bar.getCurY()) //kiểm tra tung độ
		{
			for (int j = 0; j < barLength; j++)	//Bonus cham canh tren thanh truot
			{
				if (List[i].getX() == bar.getCurX() - barLength / 2 + j)
				{
					checkBonus(List[i].getType(), score, mat, speed);
					List.erase(List.begin() + i);
					return;
				}
			}
			if (List[i].getX() == (bar.getCurX() - barLength / 2 - 1 || bar.getCurX() + barLength / 2 + 1))	//bonus cham goc tren thanh truot
			{
				checkBonus(List[i].getType(), score, mat, speed);
				List.erase(List.begin() + i);
				return;
			}
		}
		if (List[i].getY() >= HEIGHT - 2)	//Bonus chạm cạnh dưới mà không chạm Bar
		{
			List.erase(List.begin() + i);
			drawRect(0, HEIGHT - 1, WIDTH, 1, bColor, fontColor);
			return;
		}
	}
}

void CListBonus::checkBonus(int type, int& score, BrickMatrix& mat, int& speed)	//Kiem tra tac dung cua bonus
{
	switch (type)
	{
	case 1:
		score += 200;
		break;
	case 2:
		score += 500;
		break;
	case 3:
		score /= 2;
		break;
	case 4:
		score = 0;
		break;
	case 5:
		mat.setLvlAll(1);
		mat.drawBricks();
		break;
	case 6:
		mat.setLvlAll(5);
		mat.drawBricks();
		break;
	case 7:
		speed -= 15;
		break;
	case 8:
		speed += 30;
		break;
	}
}

CListBonus::CListBonus()
{
}

CListBonus::~CListBonus()
{
}