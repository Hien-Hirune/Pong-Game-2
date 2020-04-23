#pragma once
#pragma comment(lib, "winmm.lib")
#include "pch.h"
#include <malloc.h>
#include <conio.h>
#include "graphic/graphics.h"
#include <Windows.h>
#include "CBar.h"
#include "CPong.h"
#include "Point.h"'
#include "CDraw.h"
#include <ctime>
#include <chrono>
#include "BrickMatrix.h"
#include "CListBonus.h"

#define loadGameKey 10
#define pauseGame 'p'
#define resetLoop 'l'
#define WIDTH 61
#define HEIGHT 30
#define barLength 17
#define defaultSpeed 99
#define speedRange 3
#define minSpeed 7
#define botSpeed 0.02

class CGame
{
private:
	CListBonus bonus;
	CPong pong;
	CBar playerOne;
	int playerOneScore;
	int speed;
	int stage; //màn chơi
	BrickMatrix Mat;
	int highscore;
public:	
	void initial(int); // khoi tao
	void changeSpeed(); // doi toc do
	void logic(); // xet tinh logic cua game
	void run(int, int); // chay game
	bool pause(int); // tam dung game
	void displayScore(); // hien thi diem	
	void unPause(); // tiep tuc choi

	void botPlayerMove();

	void saveGame(int); // luu game
	void loadGame(int&, int&); // load game
	int getHighScore() {
		return highscore;
	}
	
	CGame();
	~CGame();
};

