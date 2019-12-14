#include "pch.h"
#include "graphic/graphics.h"


void gotoXY(int x, int y);
void setColor(int BG, int textColor);
void HideCursor();
void ShowCursor();
void drawRect(int x, int y, int width, int height, int BG, int textColor);
void drawSelection(int x, int y, std::vector <std::string> menu, int cur, int DesColor);
void drawBoard();
int drawMenu(int &order);
bool drawMenu2(std::vector <std::string> selection, int n, int &order);
void drawBar(int,int);
void drawMiddleLine();
int drawPause();
void drawWinner(int);
