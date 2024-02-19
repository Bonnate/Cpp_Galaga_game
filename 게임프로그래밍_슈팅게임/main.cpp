#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <windows.h> 
#include <time.h>
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "DeviceCtl.h"
#include "GLOBAL.h"

using namespace std;

//객체 안의 객체멤버를 각각 다른 개수로 선언하는 방법? enemy->Bullet  -> [벡터를 사용]
//Global헤더의 전역변수를 다른 모든 헤더 또는 메인에서 사용하는법? extern 변수를 사용해야하나?
//클래스를 static으로 만들어서 사용

//GLOBAL WORLD TIME
///////////////////////////////////////////
int GLOBALTIMEA = 1;
int GLOBALTIMEA_100x = 0;
///////////////////////////////////////////

//DOUBLE BUFFERING
///////////////////////////////////////////
const int SCR_HEIGHT = 70;
const int SCR_WIDTH = 110;
char front_Buffer[SCR_HEIGHT][SCR_WIDTH];
char back_Buffer[SCR_HEIGHT][SCR_WIDTH];

void moveCursurTo(const int x, const int y);
void drawToBackBuffer(const int i, const int j, const char* image);
void render();
///////////////////////////////////////////

//Init Game
///////////////////////////////////////////
Player* Player_P[2];
Enemy* ActivatedEnemy[ENEMYLV_1MAXCNT + ENEMYLV_2MAXCNT];
Bullet* Player_Bullet[2][PLAYERMAXBULLET];

int Player_1_Spped;
int Player_1_Ammo_Rapid;
int Player_1_Ammo;

int Player_2_Spped;
int Player_2_Ammo_Rapid;
int Player_2_Ammo;

int Enemy_speed;

bool g_isContinue = TRUE;

char* Text;

int MAX_PLAYERS;
///////////////////////////////////////////

//Return Global Items
///////////////////////////////////////////
int GetGLOBALTIMEA() { return GLOBALTIMEA; }
int GetMAX_PLAYERS() { return MAX_PLAYERS; }
Player* GetPlayerClass(const char Player_ID) { return Player_P[Player_ID]; }
///////////////////////////////////////////

//PreInit Fncs
///////////////////////////////////////////
bool StartProgram();
void RunGame();
void InitGame(bool is1Player);
void RunPlayer();
void RunEnemy();
void SpawnEnemy();
///////////////////////////////////////////

int main()
{
	system(" mode  con lines=70   cols=110 ");
	bool is1Player = StartProgram();
	InitGame(is1Player);
	RunGame();

	return 0;
}

void RunGame()
{
	while (g_isContinue)
	{
		//GLIBALTIME
		++GLOBALTIMEA;

		if (GLOBALTIMEA > 100)
		{
			GLOBALTIMEA = 1;
			if (GLOBALTIMEA_100x++ % 2)SpawnEnemy();
		}

		Sleep(1);

		switch (MAX_PLAYERS)
		{
		case 1:
			sprintf(Text, "%d %d %d %d %d", Player_P[0]->GetXPos(), Player_P[0]->GetYPos(), Player_P[0]->GetHP(), GLOBALTIMEA, GLOBALTIMEA_100x);
			break;

		case 2:
			sprintf(Text, "%d %d %d %d %d %d %d", Player_P[0]->GetXPos(), Player_P[0]->GetYPos(), Player_P[0]->GetHP(), Player_P[1]->GetXPos(), Player_P[1]->GetYPos(), Player_P[1]->GetHP(), GLOBALTIMEA);
			break;
		}

		drawToBackBuffer(81, 69, Text);
		RunPlayer();
		RunEnemy();

		if (MAX_PLAYERS == 1) {
			DisplayInfo(Player_P[0]->GetHP());
		}
		else {
			DisplayInfo(Player_P[0]->GetHP(), Player_P[1]->GetHP());
		}


		render();
	}
}


void InitGame(bool is1Player)
{
	//Set TextColor
	textcolor(15, 8);

	//For Test
	Text = new char[128];

	//Randomize
	srand((unsigned int)time(NULL));

	//Sets Player
	/////////////////////////
	Player_1_Spped = 6;
	Player_1_Ammo_Rapid = 10;
	Player_1_Ammo = 0;

	Player_2_Spped = 6;
	Player_2_Ammo_Rapid = 10;
	Player_2_Ammo = 0;

	//Sets Enemy Speed
	Enemy_speed = 10;

	//is 1Player plays?
	if (is1Player)
	{
		MAX_PLAYERS = 1;
		Player_P[0] = new Player(41, 65, 4);
		Player_P[1] = nullptr;

		for (int i = 0; i < PLAYERMAXBULLET; ++i)
		{
			Player_Bullet[0][i] = new Bullet;
			Player_Bullet[1][i] = nullptr;
		}
	}
	else
	{
		MAX_PLAYERS = 2;
		Player_P[0] = new Player(31, 65, 4);
		Player_P[1] = new Player(51, 65, 4);

		for (int i = 0; i < PLAYERMAXBULLET; ++i)
		{
			Player_Bullet[0][i] = new Bullet;
			Player_Bullet[1][i] = new Bullet;
		}
	}

	//Reset Screen(apply Text Color)
	for (int j = 0; j < SCR_HEIGHT; ++j)
	{
		for (int i = 0; i < SCR_WIDTH; ++i)
		{
			front_Buffer[j][i] = '.';
			back_Buffer[j][i] = '.';
		}
	}

	//Init All Enemy
	//for (int i = 0; i < ENEMYLV_1MAXCNT + ENEMYLV_2MAXCNT; ++i)
		//ActivatedEnemy[i] = nullptr;



}


void RunPlayer()
{
	//Moves Player
	switch (MAX_PLAYERS)
	{
	case 1:
		if (!(GLOBALTIMEA % Player_1_Spped))
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				Player_P[0]->CaclYPos(-1);
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				Player_P[0]->CaclYPos(1);
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				Player_P[0]->CaclXPos(-1);
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				Player_P[0]->CaclXPos(1);
			}
			if (Player_P[0]->GetXPos() <= 3)	Player_P[0]->SetXPos(3);
			if (Player_P[0]->GetXPos() >= 76)   Player_P[0]->SetXPos(76);
			if (Player_P[0]->GetYPos() <= 1)	Player_P[0]->SetYPos(1);
			if (Player_P[0]->GetYPos() > 69)	Player_P[0]->SetYPos(69);
		}

		//Ammo Rapid
		if (!(GLOBALTIMEA % Player_1_Ammo_Rapid))
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{

				if (!Player_Bullet[0][Player_1_Ammo]->f_isActive())
				{
					Player_Bullet[0][Player_1_Ammo]->f_setActive(TRUE);
					Player_Bullet[0][Player_1_Ammo++]->InitBullet(Player_P[0]->GetXPos(), Player_P[0]->GetYPos());
				}

				if (Player_1_Ammo == PLAYERMAXBULLET) Player_1_Ammo = 0;

			}

		//Display Player
		Player_P[0]->Player_Move();

		break;
	case 2:

		if (!(GLOBALTIMEA % Player_1_Spped))
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				Player_P[0]->CaclYPos(-1);
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				Player_P[0]->CaclYPos(1);
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				Player_P[0]->CaclXPos(-1);
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				Player_P[0]->CaclXPos(1);
			}
		}

		if (!(GLOBALTIMEA % Player_2_Spped))
		{
			if (GetAsyncKeyState(0x57) & 0x8000)
			{
				Player_P[1]->CaclYPos(-1);
			}
			if (GetAsyncKeyState(0x53) & 0x8000)
			{
				Player_P[1]->CaclYPos(1);
			}
			if (GetAsyncKeyState(0x41) & 0x8000)
			{
				Player_P[1]->CaclXPos(-1);
			}
			if (GetAsyncKeyState(0x44) & 0x8000)
			{
				Player_P[1]->CaclXPos(1);
			}
		}

		if (Player_P[0]->GetXPos() <= 3)	Player_P[0]->SetXPos(3);
		if (Player_P[0]->GetXPos() >= 76)   Player_P[0]->SetXPos(76);
		if (Player_P[0]->GetYPos() <= 0)	Player_P[0]->SetYPos(0);
		if (Player_P[0]->GetYPos() > 68)	Player_P[0]->SetYPos(68);
		if (Player_P[1]->GetXPos() <= 3)	Player_P[1]->SetXPos(3);
		if (Player_P[1]->GetXPos() >= 76)   Player_P[1]->SetXPos(76);
		if (Player_P[1]->GetYPos() <= 0)	Player_P[1]->SetYPos(0);
		if (Player_P[1]->GetYPos() > 68)	Player_P[1]->SetYPos(68);

		//Ammo Rapid
		if (!(GLOBALTIMEA % Player_1_Ammo_Rapid))
		{
			if (GetAsyncKeyState(0x4D) & 0x8000)
			{

				if (!Player_Bullet[0][Player_1_Ammo]->f_isActive())
				{
					Player_Bullet[0][Player_1_Ammo]->f_setActive(TRUE);
					Player_Bullet[0][Player_1_Ammo++]->InitBullet(Player_P[0]->GetXPos(), Player_P[0]->GetYPos());
				}

				if (Player_1_Ammo == PLAYERMAXBULLET) Player_1_Ammo = 0;
			}
		}

		if (!(GLOBALTIMEA % Player_2_Ammo_Rapid))
		{
			if (GetAsyncKeyState(0x46) & 0x8000)
			{

				if (!Player_Bullet[1][Player_2_Ammo]->f_isActive())
				{
					Player_Bullet[1][Player_2_Ammo]->f_setActive(TRUE);
					Player_Bullet[1][Player_2_Ammo++]->InitBullet(Player_P[1]->GetXPos(), Player_P[1]->GetYPos());
				}

				if (Player_2_Ammo == PLAYERMAXBULLET) Player_2_Ammo = 0;
			}
		}

		//Display Player
		Player_P[0]->Player_Move();
		Player_P[1]->Player_Move();

		break;
	}

	//Player Ammo Speed
	for (int i = 0; i < PLAYERMAXBULLET; ++i)
	{
		for (int j = 0; j < MAX_PLAYERS; ++j)
			if (Player_Bullet[j][i]->f_isActive())
			{
				Player_Bullet[j][i]->UseBullet_To_Enemy(ActivatedEnemy);
			}
	}

}


void RunEnemy()
{
	//Display Enemy
	for (int i = 0; i < ENEMYLV_1MAXCNT + ENEMYLV_2MAXCNT; ++i)
	{
		if (ActivatedEnemy[i] != nullptr)
		{
			ActivatedEnemy[i]->DisplayEnemy(ActivatedEnemy[i]->GetEnemyID());
		}
	}

	//Move Random Enemy
	for (int i = 0; i < ENEMYLV_1MAXCNT + ENEMYLV_2MAXCNT; ++i)
	{
		if (ActivatedEnemy[i] != nullptr && !(GLOBALTIMEA % Enemy_speed))
			switch (rand() / 100 % 8)
			{
			case 0:
				ActivatedEnemy[i]->MoveToXY(-1, -1, ActivatedEnemy);
				break;
			case 1:
				ActivatedEnemy[i]->MoveToXY(0, -1, ActivatedEnemy);
				break;
			case 2:
				ActivatedEnemy[i]->MoveToXY(1, -1, ActivatedEnemy);
				break;
			case 3:
				ActivatedEnemy[i]->MoveToXY(-1, 0, ActivatedEnemy);
				break;
			case 4:
				ActivatedEnemy[i]->MoveToXY(1, 0, ActivatedEnemy);
				break;
			case 5:
				ActivatedEnemy[i]->MoveToXY(-1, 1, ActivatedEnemy);
				break;
			case 6:
				ActivatedEnemy[i]->MoveToXY(0, 1, ActivatedEnemy);
				break;
			case 7:
				ActivatedEnemy[i]->MoveToXY(1, 1, ActivatedEnemy);
				break;
			}
	}
}






//DOUBLE BUFFERING
void moveCursurTo(const int x, const int y)
{
	const COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawToBackBuffer(const int i, const int j, const char* image)
{
	int ix = 0;
	while (1)
	{
		if (image[ix] == '\0') break;
		back_Buffer[j][i + ix] = image[ix];
		ix++;
	}
}

void render()
{
	for (int j = 0; j < SCR_HEIGHT; ++j)
		for (int i = 0; i < SCR_WIDTH; ++i)
		{
			if (back_Buffer[j][i] != front_Buffer[j][i])
			{
				moveCursurTo(i, j);

				if (back_Buffer[j][i] == '\0')
					printf("%c", ' ');

				else
					printf("%c", back_Buffer[j][i]);
			}
		}
	for (int j = 0; j < SCR_HEIGHT; ++j)
		for (int i = 0; i < SCR_WIDTH; ++i)
		{
			front_Buffer[j][i] = back_Buffer[j][i];
			back_Buffer[j][i] = '\0';
		}
}

void SpawnEnemy()
{
	if (GLOBALTIMEA_100x % 8)
		for (int i = 0; i < ENEMYLV_1MAXCNT; ++i)
		{
			if (ActivatedEnemy[i] == nullptr)
			{
				ActivatedEnemy[i] = new Enemy(i, 10, 1);
				ActivatedEnemy[i]->InitEnemy();
				return;
			}
		}

	for (int i = ENEMYLV_1MAXCNT; i < ENEMYLV_1MAXCNT + ENEMYLV_2MAXCNT; ++i)
	{
		if (ActivatedEnemy[i] == nullptr)
		{
			ActivatedEnemy[i] = new Enemy(ENEMYLV_1MAXCNT + i, 10, 2);
			ActivatedEnemy[i]->InitEnemy();
			return;
		}
	}
}