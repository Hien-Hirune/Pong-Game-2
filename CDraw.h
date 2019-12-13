#include "pch.h"
#include "graphic/graphics.h"


void gotoXY(int x, int y);
void setColor(int BG, int textColor);
void HideCursor(); //ẩn con trỏ
void ShowCursor(); //hiện con trỏ
void drawRect(int x, int y, int width, int height, int BG, int textColor);
void drawSelection(int x, int y, std::vector <std::string> menu, int cur, int BG);
void drawBoard();
int drawMenu(int &order);
void drawMenu1(int& x, int& y, std::vector <std::string> selection);
bool drawMenu2(std::vector <std::string> selection);
void drawBar(int,int);

int drawPause();
void drawWinner(int& level);