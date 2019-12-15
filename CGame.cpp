#include "pch.h"
#include "CGame.h"


// thay doi speed moi khi banh cham vao thanh choi
void CGame::changeSpeed()
{
	if (speed > minSpeed) //nếu speed chưa đạt cực đại
		speed -= speedRange; //tăng tốc cho speed (speed càng nhỏ tốc độ càng nhanh)
	else
		speed = minSpeed; 
}

void CGame::logic() 
{
	vector<CBonus> tmp;
	// xử lí va chạm cho bar
	if (pong.getCurY() + 1 == playerOne.getCurY()) //xét tung độ của bóng so với thanh chơi
	{	
		for (int i = 0; i < barLength; i++) 
		{
			if (pong.getCurX() == playerOne.getCurX() - barLength / 2 + i)
			{ //nếu bóng chạm thanh chơi thì đổi hướng bóng và tăng tốc cho bóng
				if (pong.getDir() == DOWNLEFT)
					pong.setDir(UPLEFT);
				else if (pong.getDir() == DOWNRIGHT)
					pong.setDir(UPRIGHT);
				else
					pong.setDir((dir)(rand() % 3 + 1));
				drawBar(playerOne.getCurX(), playerOne.getCurY());
				changeSpeed();
				break;
			}
		}
		if (pong.getCurX() == playerOne.getCurX() - barLength / 2 - 1) //trường hợp bóng bay xiên chạm góc trái của Bar
		{
			pong.changDir(UPLEFT);
			drawBar(playerOne.getCurX(), playerOne.getCurY());
			changeSpeed();
		}
		if (pong.getCurX() == playerOne.getCurX() + barLength / 2 + 1) //trường hợp bóng bay xiên chạm góc phải của Bar
		{
			pong.changDir(UPRIGHT);
			drawBar(playerOne.getCurX(), playerOne.getCurY());
			changeSpeed();
		}
	}
	tmp = bonus.getList();
	Mat.processTouch(pong, playerOneScore, tmp);
	bonus.setList(tmp);

	// neu dung vao thanh tren thi bat lai theo vat li
	if (pong.getCurY() - 1 <= 2) 
		pong.changDir((pong.getDir() == UPRIGHT) ? DOWNRIGHT : DOWNLEFT);

	// nếu bóng chạm thanh dưới mà không chạm thanh trượt
	if (pong.getCurY() + 1 == HEIGHT - 1)
	{
		if (drawLoser()) //nếu chọn restart
		{
			system("cls");
			int order = 0; // lua chon cua nguoi dung
			drawMenu(order); // ve menu
			if (order != 3) {
				run(order, 1); // chay game
			}
		}
		else //nếu chọn thoát
			exit(0);
	}		
	
	// thanh trai
	if (pong.getCurX() - 1 <= 2) 
		pong.changDir((pong.getDir() == UPLEFT) ? UPRIGHT : DOWNRIGHT);
	
	// thanh phai
	if (pong.getCurX() + 1 >= WIDTH - 2) 
		pong.changDir((pong.getDir() == UPRIGHT) ? UPLEFT : DOWNLEFT);
}

// khoi tao game
void CGame::initial(int level) 
{
	switch (level)
	{
	case 1:
		Mat.initLv1();
		playerOneScore = 0;
		break;
	case 2:
		Mat.initLv2();
		break;
	case 3:
		Mat.initLv3();
		break;
	case 4:
		Mat.initLv4();
		break;
	case 5:
		Mat.initLv5();
		break;
	}
	stage = level;
	Mat.drawBricks();
	drawBoard(); // ve ban choi
	drawBar(WIDTH / 2, HEIGHT - 2); // ve thanh choi
	playerOne.initial(WIDTH / 2, HEIGHT - 2);  // khoi tao nguoi choi
	pong.initial(); // khoi tao banh
	pong.draw(pongChar);	 // ve banh
	pong.randomDir(); // cho banh 1 huong chay ngau nhien
	speed = defaultSpeed;
}

// hien thi diem tren man hinh
void CGame::displayScore() {
	gotoXY(WIDTH/4 - 10, HEIGHT);
	std::cout << "Player Score: " << playerOneScore << "\t\t\t" << "Level: " << stage << std::endl;
}


// Tiep tuc choi khi pause
void CGame::unPause() {
	system("cls");
	drawBoard();
	drawBar(playerOne.getCurX(), playerOne.getCurY());
	Mat.drawBricks();
	playerOne.initial(playerOne.getCurX(), playerOne.getCurY());
	pong.draw(pongChar);
}

void CGame::reset() {
	stage = 1;
	playerOne.reset();
	playerOneScore = 0;
	pong.reset();
	pong.randomDir();
	pong.draw(delChar);
	speed = defaultSpeed;
}

//ham dieu khien bot
void CGame::botPlayerMove() 
{
	if (pong.getCurY() > HEIGHT / 3 && pong.getDir() >= 4) 
	{
		if (playerOne.getCurX() - barLength / 2 > pong.getCurX()) 
			playerOne.move(playerOneLeftControl);
		else if (playerOne.getCurX() + barLength / 2 < pong.getCurX()) 
			playerOne.move(playerOneRightControl);
		
	}
}

//ham game chay
void CGame::run(int order, int level) 
{
	system("cls");
	if (order == loadGameKey) //nếu chọn chế độ chơi tiếp thì load lại
		loadGame(order);
	else //nếu không thì khởi tạo màn chơi mới
		initial(level);

	char key;
	// ham lay thoi gian he thong de xu ly level cho bot
	auto start = std::chrono::system_clock::now();
	auto startGame = std::chrono::system_clock::now();
	double botRunTime = botSpeed;

	while (1)
	{
		if (_kbhit()) { // neu co nhan input tu ban phim 
			key = _getch(); // lay phim
			switch (key)
			{
			case resetLoop:
				pong.outLoop();
				playerOneScore -= 200;
				break;
			case pauseGame:
				if (pause(order)) //nếu người chơi muốn exit
					exit(0);
				break;
			case playerOneLeftControl:
				if (order == 1)
					playerOne.move(playerOneLeftControl);
				break;
			case playerOneRightControl:
				if (order == 1)
					playerOne.move(playerOneRightControl);
				break;
			case resetButton:
				for (int i = 0; i < 29; i++) {
					gotoXY(65 + i, 15);
					cout << " ";
				}
				pong.randomDir();
				stage = 1;
				start = std::chrono::system_clock::now();
				break;
			default:
				break;
			}
		}

		auto end = std::chrono::system_clock::now();
		// tinh toan thoi gian choi de tang level cho bot va thoi gian bot duoc phep di chuyen
		std::chrono::duration<double> elapsed_seconds = end - start;
		if (elapsed_seconds.count() >= botRunTime)
		{
			if (order == 2) //nếu chọn chế độ chơi cho bot
				botPlayerMove();

			start = std::chrono::system_clock::now();
			std::chrono::duration<double> stageTime = end - startGame;
			if (stageTime.count() >= 5) {
				startGame = std::chrono::system_clock::now();
				if (rand() % 2 == 0) {
					botRunTime -= 0.01;
				}
				else {
					botRunTime += 0.01;
				}
			}
		}
		
		
		logic(); //xét logic va chạm bóng
		displayScore(); // hiển thị điểm

		pong.draw(delChar); // xóa bóng
		pong.Move(); // di chuyển bóng
		pong.draw(pongChar); // vẽ bóng
		bonus.Erase();
		bonus.logic(playerOne, playerOneScore, Mat, speed);
		bonus.Move();
		bonus.draw();
		Sleep(speed);

		if (Mat.win()) //nếu người chơi thắng
		{
			drawWinner(level);
			if (level == 1) //nếu lựa chọn restart
			{
				int k = 0; // lua chon cua nguoi dung
				drawMenu(k); // ve menu
				if (k != 3) 
					run(k, level); // chay game
			}
			else run(order, level); //nếu lựa chọn chơi tiếp
		}
	}
}



// day la ham luu game
void CGame::saveGame(int choice) {
	freopen("input.txt", "wt", stdout);// mo file 
	// luu cac thong tin can thiet
	std::cout << playerOne.getCurX() << " " << playerOne.getCurY() << " " << playerOneScore << std::endl;
	std::cout << pong.getCurX() << " " << pong.getCurY() << " " << pong.getDir() << std::endl;
	std::cout << choice << " " << stage << endl;
	for (int i = 0; i < Mat.getRow(); i++)
	{
		for (int j = 0; j < Mat.getCol(); j++)
		{
			std::cout << Mat.getBrick(i, j).getLevel() << " ";
		}
	}
	freopen("CON", "wt", stdout);
	// chuyeen lai input sang console
}

// ham mo lai game da luu
void CGame::loadGame(int& choice) {
	freopen("input.txt", "rt", stdin);
	int x, y;
	std::cin >> x >> y >> playerOneScore;
	playerOne.setCur(x, y);
	std::cin >> x >> y;
	pong.setCur(x, y);
	int direct;
	std::cin >> direct;
	pong.setDir(direct);
	std::cin >> choice;
	std::cin >> stage;
	switch (stage)
	{
	case 1:
	case 2:
		Mat.setCur(3, 10, 3);
		break;
	case 3:
	case 4:
	case 5:
		Mat.setCur(4, 10, 3);
		break;
	}
	for (int i = 0; i < Mat.getRow(); i++)
	{
		for (int j = 0; j < Mat.getCol(); j++)
		{
			std::cin >> x;
			Mat.getBrick(i, j).setLevel(x);
		}
	}
	freopen("CON", "rt", stdin);
	drawBoard();
	Mat.drawBricks();
	drawBar(playerOne.getCurX(), playerOne.getCurY());
	playerOne.initial(playerOne.getCurX(), playerOne.getCurY());
	pong.draw(pongChar);
}

// ham dung game
bool CGame::pause(int order) //false nếu chơi tiếp, true nếu thoát game
{
	system("cls");
	if (drawPause() == 0) //nếu người chơi nhấn continue
	{
		unPause();
		return false;
	}
	else //ngược lại nếu nhấn exit
	{
		saveGame(order);	
		return true;
	}
}

CGame::CGame()
{
	srand(time(NULL));
	speed = defaultSpeed;
	quit = false;
	playerOneScore = 0;
	stage = 1;
}

CGame::~CGame()
{
}
