#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <windows.h> 
#include <time.h>
using namespace std;
int GetGLOBALTIMEA();

#include "Bullet.h"
#include "Player.h"
#include "GLOBAL.h"


Bullet::Bullet() : b_Damage(2), b_xPos(0), b_yPos(0), isActive(FALSE) { }

void Bullet::UseBullet_To_Enemy(Enemy* enemyClass[])
{
	for (int j = 0; j < ENEMYLV_1MAXCNT + ENEMYLV_2MAXCNT; ++j)
	{
		if (enemyClass[j] != nullptr && enemyClass[j]->CheckCrash(b_xPos, b_yPos))
		{
			isActive = FALSE;
			enemyClass[j]->GetDamage(b_Damage);
			if (!enemyClass[j]->f_isActive())
			{
				Enemy* temp = enemyClass[j];
				enemyClass[j] = nullptr;
				delete temp;
			}
		}
	}

	if (b_yPos < 0)
	{
		isActive = FALSE;
		return;
	}

	drawToBackBuffer(b_xPos, --b_yPos, "A");
}

void Bullet::Bullet_To_Player(Player* PlayerClass, const char EnemyLVID)
{
	if (PlayerClass->CheckCrash(b_xPos, b_yPos, 1))
	{
		isActive = FALSE;
		PlayerClass->GetDamage(1);
	}
	switch (EnemyLVID)
	{
	case 1:
		if (!(GetGLOBALTIMEA() % 5))
		{
			drawToBackBuffer(b_xPos, ++b_yPos, "0");
		}
		else
		{
			drawToBackBuffer(b_xPos, b_yPos, "0");
		}

		break;

	case 2:
		if (!(GetGLOBALTIMEA() % 5))
		{
			drawToBackBuffer(b_xPos, ++b_yPos, "0");
		}
		else
		{
			drawToBackBuffer(b_xPos, b_yPos, "0");
		}
		break;
	}


	if (b_yPos > 68)	isActive = FALSE;
}

void Bullet::RemoveBullet()
{
	isActive = FALSE;
}

void Bullet::InitBullet(int xPos, int yPos)
{
	b_xPos = xPos;
	b_yPos = yPos;
	isActive = TRUE;
}

bool Bullet::f_isActive()
{
	return isActive;
}

void Bullet::f_setActive(bool _flag)
{
	isActive = _flag;
}
