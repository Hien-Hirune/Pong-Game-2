#include "pch.h"
#include "CDraw.h"

#define D 3					// khoang cach giua cac o chon
#define xStart 40			// vi tri x dau tien
#define firstMenuY 5
#define secondMenuY 3
#define yStart 5			// vi tri y dau tien
#define bColor 4			// mau ban dau
#define smallBox 40 			// do dai cua cac o lua chon
#define	fontColor 7			// mau chu
#define WIDTH 61
#define HEIGHT 30

#define loadGame 10

#define barLength 17
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

void drawSelection(int x, int y, std::vector <std::string> menu, int cur, int DesColor) // ve cac o lua chon
{
	drawRect(x, y, smallBox, 2, DesColor, 2); // ve hcn
	int pos = menu[cur].length() / 2; // tinh vi tri
	gotoXY(x + (smallBox / 2 - pos), y); // can giua hinh chu nhat
	setColor(DesColor, fontColor); // doi mau sang mau khac khi con nguoi dung tro toi
	std::cout << menu[cur];			   // in ra chu trong o lua chon
	setColor(0, fontColor);			// tra ve mau ban dau 
}

int drawPause() 
{
	int x = xStart, y = yStart + secondMenuY;
	std::vector <std::string> selection;
	selection.push_back("CONTINUE\0");
	selection.push_back("SAVE & EXIT!");
	
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

bool drawMenu2(std::vector <std::string> selection, int n, int &order)
{
	HideCursor();
	int distance = 5;
	char c;
	int cur = 3;									// vi tri cua text trong selection
	int x = xStart, y = yStart + secondMenuY;
	drawSelection(x, y, selection, 3, 6);          // ve ra 2 cai o trong selection 2
	drawSelection(x, y + D, selection, 4, bColor);
	drawSelection(x, y + D * 2, selection, 5, bColor);

	while (1)
	{
		c = getch();  // nhan vao lua chon cua nguoi dung
		if (c == 72 && cur != 3)  // mui ten di len
		{
			drawSelection(x, y - D, selection, cur - 1, 6); // ve hcn o tren mau khac
			drawSelection(x, y, selection, cur, bColor);		// ve hinh chu nhat o duoi mau ban dau
			y -= D;									// di chuyen con tro len tren
			gotoXY(x, y);
			cur -= 1;

		}
		else if (c == 80 && cur != n)
		{
			drawSelection(x, y + D, selection, cur + 1, 6); // ve hcn o duoi mau khac
			drawSelection(x, y, selection, cur, bColor);// ve hinh chu nhat o tren mau ban dau
			y += D;									// di chuyen con tro xuong duoi
			gotoXY(x, y);
			cur += 1;
		}
		else if (c == 13)
		{
			if (cur == 5) // neu con tro o o Back thi quay lai selection 1
			{
				system("CLS");
				return true;
			}
			else if (cur == 4) {
				order = 2;
				return 1;
			}
			else if (cur == 3) {
				order = 1;
				return 1;
			}
		}
	}
	setColor(0, fontColor); // set lai mau ban dau
}
// ve thanh o giua ban choi 
void drawMiddleLine() {
	for (int i = 1; i < HEIGHT / 2 - 1; i++) {
		if (i*2 != HEIGHT / 2 - 1) {
			gotoXY(WIDTH / 2 - 1, i * 2);
			std::cout << "\xDD";
		}
	}
}
// ve ban` choi 
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
		gotoXY(x - barLength / 2 + i, y);
		std::cout << barChar;
	}
}

// ve bang hien thi nguoi thang cuoc
void drawWinner(int player) {
	int x = xStart, y = yStart + 9;
	std::vector <std::string> selection;
	if (player == 1) {
		selection.push_back("Player One Win !!!");
	}
	else {
		selection.push_back("Player Two Win !!!");
	}
	drawSelection(x, y, selection, 0, RED);

}

// ve menu dau tien
int drawMenu(int &order) {
	HideCursor();
	std::vector <std::string> selection;
	selection.resize(8);
	selection[0] = "START GAME\0";
	selection[1] = "LOAD GAME\0";
	selection[2] = "EXIT\0";
	selection[3] = "1 PLAYER\0";
	selection[4] = "2 PLAYER\0";
	selection[5] = "BACK\0";
	
	int n = selection.size() - 1;
	int distance = 5;
	char c;
	int cur = 0;
	int x = xStart, y = yStart + firstMenuY;

	// ve cac o lua chon ban dau
	drawSelection(x, y, selection, 0, bColor);
	drawSelection(x, y + D, selection, 1, bColor);
	drawSelection(x, y + D * 2, selection, 2, bColor);
	drawSelection(x, y, selection, 0, 6);
	while (1)
	{
		c = getch();    // nhan vao lua chon cua nguoi dung
		if (c == 72 && cur != 0)  // mui ten di len
		{
			drawSelection(x, y - D, selection, cur - 1, 6);  // ve hcn o tren mau khac
			drawSelection(x, y, selection, cur, bColor);		// ve hcn o duoi mau ban dau
			y -= D;										// di chuyen con tro toi vi tri tiep theo
			gotoXY(x, y);
			cur -= 1;

		}
		else if (c == 80 && cur != 2)	// mui ten xuong
		{
			drawSelection(x, y + D, selection, cur + 1, 6); // ve hcn o duoi mau khac
			drawSelection(x, y, selection, cur, bColor);		// ve hcn o tren mau ban dau
			y += D;										// di chuyen con tro toi vi tri tiep theo
			gotoXY(x, y);
			cur += 1;
		}
		else if (c == 13)
		{
			if (cur == 0) 
			{
				system("CLS");
				if (drawMenu2(selection, n, order)) // vao ve ham 2 
				{
					if (order == 1 || order == 2) {
						return order;
					}
					// ve lai menu 1 neu nhu nguoi dung BACK o menu 2
					drawSelection(x, y, selection, 0, bColor);
					drawSelection(x, y + D, selection, 1, bColor);
					drawSelection(x, y + D * 2, selection, 2, bColor);
					
				}
				else
				{
					setColor(0, 7);
					return order;
				}
			}
			else if (cur == 2) {
				std::cout << std::endl << std::endl;
				exit(0); // thoat neu nguoi dung vao o THOAT
			}
			else if (cur == 1) {
				order = loadGame;
				return order;
			}
		}
	}
	setColor(0, 7);
	system("CLS");
	return order;
}

