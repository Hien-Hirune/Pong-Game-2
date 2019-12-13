﻿#include "pch.h"
#include "CDraw.h"

#define D 4					// khoang cach giua cac o chon
#define xStart 40			// vi tri x dau tien
#define firstMenuY 5
#define secondMenuY 3
#define yStart 5			// vi tri y dau tien
#define bColor 4			// màu bg ban đầu là màu đỏ
#define smallBox 40 			// do dai cua cac o lua chon
#define	fontColor 15			// màu chữ trắng
#define WIDTH 61
#define HEIGHT 30

#define loadGame 10

#define barLength 7
#define barChar '\xDB'

int theColor[9] = { 10,11,12,13,14,6,5,9 };
int numberColor = 0;

void gotoXY(int x, int y)	//Ham tro giup ve khung menu (di den toa do x,y trong console)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setColor(int BG, int textColor)	//Thay doi mau chu va nen chu trong console
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BG << 4 | textColor);
}

//an di con tro trong console
void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

//hien thi lai con tro trong console
void ShowCursor()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void drawRect(int x, int y, int width, int height, int BG, int textColor)	//Ve hinh chu nhat
{
	setColor(BG, textColor);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			gotoXY(x + i, y + j);
			std::cout << " ";	//Khoang trang nhung co mau (to mau)
		}
	}
	setColor(0, fontColor);
}

void drawSelection(int x, int y, std::vector <std::string> menu, int cur, int BG) // vẽ ô lựa chọn menu[cur] với màu nền BG
{
	drawRect(x, y, smallBox, 3, BG, fontColor); // ve hcn
	int pos = menu[cur].length() / 2; // tính vị trí chính giữa của chữ 
	gotoXY(x + (smallBox / 2 - pos), y + 1); // căn giữa hcn
	setColor(BG, fontColor); // doi mau sang mau khac khi con nguoi dung tro toi
	std::cout << menu[cur];			   // in ra chu trong o lua chon
	setColor(0, fontColor);			// tra ve mau ban dau 
}

int drawPause() 
{
	int x = xStart, y = yStart + 3;
	std::vector <std::string> selection;
	selection.push_back("CONTINUE\0");
	selection.push_back("SAVE GAME & EXIT\0");
	
	drawSelection(x, y, selection,0, 6);          // ve ra 2 cai o trong selection 2
	drawSelection(x, y + D, selection, 1, bColor);
	int cur = 0;
	char c;
	while (1)
	{
		c = getch();  // nhan vao lua chon cua nguoi dung
		if (c == 72 && cur != 0)  // mui ten di len
		{
			drawSelection(x, y - D, selection, cur - 1, 6); // ve hcn o tren mau khac
			drawSelection(x, y, selection, cur, bColor);		// ve hinh chu nhat o duoi mau ban dau
			y -= D;									// di chuyen con tro len tren
			gotoXY(x, y);
			cur -= 1;

		}
		else if (c == 80 && cur != 1)
		{
			drawSelection(x, y + D, selection, cur + 1, 6); // ve hcn o duoi mau khac
			drawSelection(x, y, selection, cur, bColor);// ve hinh chu nhat o tren mau ban dau
			y += D;									// di chuyen con tro xuong duoi
			gotoXY(x, y);
			cur += 1;
		}
		else if (c == 13)
		{
			if (cur == 0) {
				return 1;
			}
			else if (cur == 1) {
				return 2;
			}
		}
	}
	setColor(0, fontColor); // set lai mau ban dau
}

bool drawMenu2(std::vector <std::string> selection)
{
	HideCursor();
	char c;
	//int cur = 3;	// vi tri cua text trong selection
	int x = xStart, y = yStart + 3;
	drawSelection(x, y, selection, 5, bColor);
	drawSelection(x, y + D, selection, 6, bColor);
	drawSelection(x, y + D * 2, selection, 4, 9);  // vẽ lựa chọn trong menu 2
	while (1)
	{
		c = getch();  // nhan vao lua chon cua nguoi dung
		if (c == 13) //nếu nhấn enter
		{
			system("CLS");
			return true;
		}
	}
	setColor(0, fontColor); // set lai mau ban dau
}
void drawBoard() 
{
	drawRect(0, 0, WIDTH, 1, bColor, fontColor);
	drawRect(0, 0, 1, HEIGHT, bColor, fontColor);
	drawRect(WIDTH - 1, 0, 1, HEIGHT, bColor, fontColor);
	drawRect(0, HEIGHT - 1, WIDTH, 1, bColor, fontColor);
}

// ve thanh choi
void drawBar(int x, int y) 
{
	for (int i = 0; i < barLength; i++) 
	{
		gotoXY(x, y - barLength/2 + i);
		std::cout << barChar;
	}
}

// ve bang hien thi nguoi thang cuoc
void drawWinner(int& level) 
{
	HideCursor();
	int x = xStart, y = yStart + 4;
	std::vector <std::string> selection;
	if (level == 5) //nếu chơi đến max level rồi thì không có continue game nữa
	{
		selection.push_back("YOU WIN!!!");
		selection.push_back("RESTART GAME\0");
	}
	else
	{
		selection.push_back("LEVEL UP!!!");
		selection.push_back("CONTINUE GAME\0");
	}
	selection.push_back("SAVE GAME & EXIT\0");

	//vẽ ô lựa chọn
	drawSelection(x, y, selection, 0, bColor);
	drawSelection(x, y + D, selection, 1, 6); //set ô lựa chọn đầu 
	drawSelection(x, y + D * 2, selection, 2, bColor);

	int cur = 1;
	char c;
	y += D;
	while (1)
	{
		c = getch();  // nhan vao lua chon cua nguoi dung
		if (c == 72 && cur != 1)  // nếu gặp mũi tên đi lên và chưa chạm ô đầu tiên
		{
			drawSelection(x, y - D, selection, cur - 1, 6); // ve hcn o tren mau khac
			drawSelection(x, y, selection, cur, bColor);		// ve hinh chu nhat o duoi mau ban dau
			y -= D;									// di chuyen con tro len tren
			gotoXY(x, y);
			cur -= 1;
		}
		else if (c == 80 && cur != 2) // nếu gặp mũi tên đi xuống và chưa chạm ô cuối cùng
		{
			drawSelection(x, y + D, selection, cur + 1, 6); // ve hcn o duoi mau khac
			drawSelection(x, y, selection, cur, bColor);// ve hinh chu nhat o tren mau ban dau
			y += D;									// di chuyen con tro xuong duoi
			gotoXY(x, y);
			cur += 1;
		}
		else if (c == 13)
		{
			if (cur == 2) //nếu lựa chọn thoát
			{
				std::cout << std::endl << std::endl << std::endl;
				exit(0);
			}
			else if (cur == 1 && level < 5) //nếu lựa chọn chơi tiếp
			{
				level++; //tăng level
			}
			else if (cur == 1 && level == 5) //nếu lựa chọn restart game
			{
				level = 1;

			}
		}
	}
	setColor(0, fontColor); // set lai mau ban dau
	std::cout << std::endl << std::endl << std::endl;
	system("CLS");
}

// ve menu dau tien
int drawMenu(int &order) 
{
	HideCursor();
	std::vector <std::string> selection;
	selection.resize(10);
	selection[0] = "START NEW GAME\0";
	selection[1] = "CONTINUE GAME\0";
	selection[2] = "HOW TO PLAY\0";
	selection[3] = "SAVE GAME & EXIT\0";
	selection[4] = "BACK\0";
	selection[5] = "Press -> to move right\0";
	selection[6] = "Press <- to move left\0";
	char c;
	int x, y, cur = 0;
	drawMenu1(x, y, selection); //vẽ lựa chọn menu 1
	drawSelection(x, y, selection, 0, 9); //set lại ô đầu màu xanh dương
	while (1)
	{
		c = getch();    // nhan vao lua chon cua nguoi dung
		if (c == 72 && cur != 0)  // nếu gặp mũi tên đi lên và chưa chạm ô đầu tiên
		{
			drawSelection(x, y - D, selection, cur - 1, 9);  // ve hcn o tren mau khac
			drawSelection(x, y, selection, cur, bColor);		// ve hcn o duoi mau ban dau
			y -= D;										// di chuyen con tro toi vi tri tiep theo
			gotoXY(x, y); //di chuyển tới ô được chọn
			cur -= 1;
		}
		else if (c == 80 && cur != 3)	// nếu gặp mũi tên đi xuống và chưa chạm ô cuối cùng
		{
			drawSelection(x, y + D, selection, cur + 1, 9); // ve hcn o duoi mau khac
			drawSelection(x, y, selection, cur, bColor);		// ve hcn o tren mau ban dau
			y += D;										// di chuyen con tro toi vi tri tiep theo
			gotoXY(x, y); //di chuyển tới ô được chọn 
			cur += 1;
		}
		else if (c == 13) //nếu gặp phím enter
		{
			if (cur == 0)
				return order;
			if (cur == 1) //nếu tiếp tục chơi
			{
				order = loadGame;
				return order;
			}
			if (cur == 2)
			{
				system("CLS");
				if (drawMenu2(selection)) // nếu người dùng quay về menu 1
				{
					// vẽ lại menu 1 
					drawMenu1(x, y, selection);
					cur = 0; //set lại ô lựa chọn = 0
				}
			}
			else if (cur == 3)
			{
				std::cout << std::endl << std::endl << std::endl;
				exit(0); // thoat neu nguoi dung vao o THOAT
			}
		}
	}
	setColor(0, 15);
	system("CLS");
	return order;
}

void drawMenu1(int &x, int &y, std::vector <std::string> selection)
{
	x = xStart; y = yStart + 3;
	// ve cac o lua chon ban dau
	drawSelection(x, y, selection, 0, 9); //set lại ô đầu màu xanh dương
	drawSelection(x, y + D, selection, 1, bColor); //1 là vị trí lựa chọn trong selection
	drawSelection(x, y + D * 2, selection, 2, bColor);
	drawSelection(x, y + D * 3, selection, 3, bColor);
}

