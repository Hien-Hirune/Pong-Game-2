// 18120172.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "CGame.h"
#include "BrickMatrix.h"

int main()
{
	CGame a; // tao game
	bool music = PlaySound(L"TheFatRat.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	while (!music) //repeat lại khi hết nhạc
	{
		PlaySound(L"TheFatRat.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	int order = 0; // lua chon cua nguoi dung
	drawMenu(order); // ve menu
	if (order != 3) {
		a.run(order, 1); // chay game
	}
}

