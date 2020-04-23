#include "pch.h"
#include "graphic/graphics.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


void gotoXY(int x, int y);
void setColor(int BG, int textColor);
void HideCursor();
void ShowCursor();
void drawRect(int x, int y, int width, int height, int BG, int textColor);
void drawSelection(int x, int y, std::vector <std::string> menu, int cur, int DesColor);
void drawBoard();
void drawTitle();
int drawMenu(int &order);
void drawMenu1(int& x, int& y, std::vector <std::string> selection);
bool drawMenu2(std::vector <std::string> selection);
int drawMenuPlay(std::vector <std::string> selection);
void drawBar(int,int);
void drawScore(int, int, int);

int drawPause();
void drawWinner(int&, int);
bool drawLoser(int);

