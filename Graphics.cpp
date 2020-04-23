#include "pch.h"
#include <iostream>
#include <string>
#include "windows.h"
#include <conio.h>
#include "Variables.h"
#include "Menu.h"
using namespace std;


/*
	XX --->BackgroundText
	0 black
	1 blue
	2 green
	3 aqua
	4 red
	5 purple
	6 yellow
	7 white
	8 gray
	9 light blue
	10 light green
	11 light aqua
	12 light red
	13 light purple
	14 light yellow
	15 bright white
	colorattribute = foreground + background * 16

*/

//hide cursor
void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

//showcursor
void ShowCursor()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void FixConsoleWindow(int width, int height)
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	/*RECT r;
	GetWindowRect(consoleWindow,&r);
	MoveWindow(consoleWindow, r.left, r.top, width, height, TRUE);*/
	//disable scrollbar
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y - 14;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

	//ShowScrollBar(consoleWindow, SB_BOTH, FALSE);
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0)
{
	GotoXY(x, y); cout << "X";
	for (int i = 1;i < width;i++)
		cout << "X";
	cout << "X";
	GotoXY(x, height + y);
	cout << "X";
	for (int i = 1;i < width;i++)
		cout << "X";
	cout << "X";
	for (int i = y + 1;i < height + y;i++)
	{
		GotoXY(x, i);
		cout << "X";
		GotoXY(x + width, i);
		cout << "X";
	}
	GotoXY(curPosX, curPosY);
}

void setColor(int color, int bgColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | color);
}

void drawRect(int x, int y, int width, int height, int color, int bgColor)
{
	setColor(color, bgColor);
	for (int j = 0; j < height; j++)
	{
		GotoXY(x, y + j);
		for (int i = 0; i < width;i++)
			cout << " ";
	}
	setColor(7, 0);
}

void doAction(int num)
{
	switch (num)
	{
	case 0:
		NewGame();
		break;
	case 1:
		LoadGameMenu();
		break;
	case 2:
		exit(0);
		break;
	default:	
		break;
	}
}

void drawTitle(int x, int y)
{
	
	//S
	drawRect(20, 3, 6, 1, 0, 10);
	drawRect(20, 4, 2, 2, 0, 10);
	drawRect(20, 5, 6, 1, 0, 10);
	drawRect(24, 6, 2, 2, 0, 10);
	drawRect(20, 7, 6, 1, 0, 10);

	//N
	drawRect(28, 3, 2, 5, 0, 10);
	drawRect(34, 3, 2, 5, 0, 10);
	setColor(0, 10);
	GotoXY(30, 4); cout << " ";
	GotoXY(31, 5); cout << " ";
	GotoXY(32, 6); cout << " ";
	GotoXY(33, 7); cout << " ";
	
	//A
	drawRect(38, 3, 2, 5, 0, 10);
	drawRect(44, 3, 2, 5, 0, 10);
	drawRect(38, 3, 6, 1, 0, 10);
	drawRect(38, 5, 6, 1, 0, 10);

	//K
	drawRect(48, 3, 2, 5, 0, 10);
	setColor(0, 10);
	GotoXY(50, 5); cout << "  ";
	GotoXY(52, 4); cout << "  ";
	GotoXY(54, 3); cout << "  ";
	GotoXY(52, 6); cout << "  ";
	GotoXY(54, 7); cout << "  ";

	//A
	drawRect(58, 3, 2, 5, 0, 10);
	drawRect(58, 3, 6, 1, 0, 10);
	drawRect(58, 5, 6, 1, 0, 10);
	drawRect(58, 7, 6, 1, 0, 10);
}

void drawMenu(int x, int y)
{
	system("cls");
	HideCursor();
	drawTitle(20,0);
	int list = 3;
	int current = 0;
	string feature[3];
	feature[0] = "PLAY GAME";
	feature[1] = "LOAD GAME";
	feature[2] = "EXIT GAME";
	drawRect(x, y, 25, list, 14, 3);
	for (int i = 0;i < list;i++)
	{
		if (i == 0)
		{
			drawRect(x, y, 25, 1, 14, 1);
			setColor(14, 1);
		}
		else
			setColor(14, 3);
		GotoXY(x + 8, y + i);
		cout << feature[i];
	}
	GotoXY(x, y);
	setColor(7, 0);
	// up = 72 down = 80 esc 27
	char ch = _getch();
	while (1)
	{
		if (ch == 'T')
		{
			doAction(1);
			break;
		}
		// move up
		if (ch == 72 && current > 0)
		{
			drawRect(x, y + current, 25, 1, 14, 3);
			GotoXY(x + 8, y + current);
			setColor(14, 3);
			cout << feature[current];

			current--;
			drawRect(x, y+current, 25, 1, 14, 1);
			GotoXY(x+8, y + current);
			setColor(14, 1);
			cout << feature[current];
			GotoXY(x, y + current);
			setColor(7, 0);
		}
		if (ch == 80 && current < list - 1)
		{
			drawRect(x, y + current, 25, 1, 14, 3);
			GotoXY(x + 8, y + current);
			setColor(14, 3);
			cout << feature[current];

			current++;
			drawRect(x, y + current, 25, 1, 14, 1);
			GotoXY(x + 8, y + current);
			setColor(14, 1);
			cout << feature[current];
			GotoXY(x, y + current);
			setColor(7, 0);
		}
		if (ch == 13)
		{
			doAction(current);
			break;
		}
		ch = _getch();
	}
}

void notifyBoard(int x, int y, string noti)
{
	drawRect(x, y, 25, 4, 14, 4);
	setColor(14, 4);
	GotoXY(x + 6, y + 1);
	cout << "INVALID INPUT";
	GotoXY(x + 4, y + 2);
	cout << noti;
	setColor(7, 0);
	Sleep(1000);
}

void loadingBoard(int x, int y, string noti)
{

}
