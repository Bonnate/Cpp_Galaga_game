#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <windows.h> 
#include <time.h>
using namespace std;
int GetGLOBALTIMEA();
int GetMAX_PLAYERS();

#include "Enemy.h"
#include "Player.h"
#include "GLOBAL.h"


Player* GetPlayerClass(const char Player_ID);

Enemy::Enemy(char _id, int _HP, const char _Enemy_LV_ID) : ID(_id), e_HP(_HP), Enemy_LV_ID(_Enemy_LV_ID), isActive(FALSE), BulletPos(0)
{
	switch (_Enemy_LV_ID)
	{
	case 1:
		for (int i = 0; i < ENEMYLV_1MAXBULLET; ++i) EnemyBullet[i] = new Bullet;
		Enemy::_InherenceIndex = rand() % 50 + 30;
		break;

	case 2:
		for (int i = 0; i < ENEMYLV_2MAXBULLET; ++i) EnemyBullet[i] = new Bullet;
		Enemy::_InherenceIndex = rand() % 10 + 30;
		break;
	}
}

void Enemy::InitEnemy()
{
	e_xPos = rand() % 74 + 3;
	e_yPos = 1;
	isActive = TRUE;
}

void Enemy::Shoot(const char _Enemy_LV_ID)
{
	switch (_Enemy_LV_ID)
	{

	case 1:
		if (!(GetGLOBALTIMEA() % _InherenceIndex))
			if (!EnemyBullet[BulletPos]->f_isActive())
			{
				EnemyBullet[BulletPos++]->InitBullet(e_xPos, e_yPos + 1);
				if (BulletPos == ENEMYLV_1MAXBULLET) BulletPos = 0;
			}

		for (int i = 0; i < ENEMYLV_1MAXBULLET; ++i)
		{
			for (int j = 0; j < GetMAX_PLAYERS(); ++j)
			{
				if (EnemyBullet[i]->f_isActive())EnemyBullet[i]->Bullet_To_Player(GetPlayerClass(j), Enemy_LV_ID);
			}
		}
		break;

	case 2:
		if (!(GetGLOBALTIMEA() % _InherenceIndex))
			if (!EnemyBullet[BulletPos]->f_isActive())
			{
				EnemyBullet[BulletPos++]->InitBullet(e_xPos, e_yPos + 1);
				if (BulletPos == ENEMYLV_2MAXBULLET) BulletPos = 0;
			}

		for (int i = 0; i < ENEMYLV_2MAXBULLET; ++i)
		{
			for (int j = 0; j < GetMAX_PLAYERS(); ++j)
			{
				if (EnemyBullet[i]->f_isActive())EnemyBullet[i]->Bullet_To_Player(GetPlayerClass(j), Enemy_LV_ID);
			}
		}
		break;
	}
	
}

bool Enemy::CheckCrash(int _TargetX, int _TargetY, int TargetSize)
{
	return (e_xPos - TargetSize <= _TargetX && e_xPos + TargetSize >= _TargetX)
		&& (e_yPos - TargetSize <= _TargetY && e_yPos + TargetSize >= _TargetY);
}

void Enemy::GetDamage(int _damage)
{
	e_HP -= _damage;
	if (e_HP <= 0) isActive = FALSE;
}

void Enemy::MoveToXY(const int _x, const int _y, Enemy* Enemy[])
{
	for (int i = 0; i < ENEMYLV_1MAXCNT; ++i)
		if (Enemy[i] != nullptr && Enemy[i]->CheckCrash(e_xPos + _x, e_yPos + _y, 1) && ID != Enemy[i]->ID)
		{
			e_xPos -= _x;
			e_yPos -= _y;

			if (e_xPos <= 2)	e_xPos ++;
			if (e_xPos >= 78)	e_xPos --;
			return;
		}

	for (int i = ENEMYLV_1MAXCNT; i < ENEMYLV_1MAXCNT + ENEMYLV_2MAXCNT; ++i)
		if (Enemy[i] != nullptr && Enemy[i]->CheckCrash(e_xPos + _x, e_yPos + _y, 3) && ID != Enemy[i]->ID)
		{
			e_xPos -= _x;
			e_yPos -= _y;

			if (e_xPos <= 2)	e_xPos ++;
			if (e_xPos >= 78)	e_xPos --;
			return;
		}

	e_xPos += _x;
	e_yPos += _y;

	if (e_xPos <= 2)	e_xPos ++;
	if (e_xPos >= 78)	e_xPos --;
	if (e_yPos <= 4)	++e_yPos;
	if (e_yPos > 30)	--e_yPos;
}

bool Enemy::f_isActive()
{
	return isActive;
}

void Enemy::DisplayEnemy(const char Enemy_LV_ID)
{
	Enemy::Shoot(Enemy_LV_ID);

	switch (Enemy_LV_ID)
	{
	case 1:
		drawToBackBuffer(e_xPos - 3, e_yPos, "*-0-*");
		drawToBackBuffer(e_xPos - 3, e_yPos + 1, "[   ]");

		break;

	case 2:
		drawToBackBuffer(e_xPos - 3, e_yPos, "__ | __");
		drawToBackBuffer(e_xPos - 4, e_yPos + 1, "@--(_)--@");
		
		break;

	}
}

const char Enemy::GetEnemyID()
{
	return Enemy_LV_ID;
}

Enemy::~Enemy() 
{
	for (int i = 0; i < ENEMYLV_1MAXBULLET; ++i)
		delete EnemyBullet[i];
}