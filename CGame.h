#pragma once
#include "pch.h"
#include <malloc.h>
#include <conio.h>
#include "graphic/graphics.h"
#include "CBar.h"
#include "CPong.h"
#include "Point.h"'
#include "CDraw.h"
#include <ctime>
#include <chrono>
#include "BrickMatrix.h"
#include "CListBonus.h"

#define resetButton 'r'

#define loadGameKey 10

#define pauseGame 'p'

#define resetLoop 'l'

#define WIDTH 61
#define HEIGHT 30


#define barLength 17

#define speedRange 3
#define defaultSpeed 50
#define minSpeed 10
#define botSpeed 0.02
#define winPoint 3
class CGame
{
private:
	CListBonus bonus;
	CPong pong;
	CBar playerOne;
	bool quit;
	int playerOneScore;
	int speed;
	int stage;
	BrickMatrix Mat;
public:	
	void upScore(CBar player); // tang diem
	void initial(); // khoi tao
	void changeSpeed(); // doi toc do
	void logic(); // xet tinh logic cua game
	void run(int); // chay game
	bool pause(int); // tam dung game
	void botPlayerMove(); // cho bot chay
	void displayScore(); // hien thi diem
	int setBotColor(); // thay doi mau cua bot
	void reset(); // khoi tao lai game
	void unPause(); // tiep tuc choi
	void botLevelUp(); // tang cap cho bot
	void saveGame(int choice); // luu game
	void loadGame(int&); // load game
	void displayWinner(int ); // hien thi nguoi win
	CGame();
	~CGame();
};

