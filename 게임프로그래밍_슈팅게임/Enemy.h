#pragma once

class Bullet; 

#include "Bullet.h"
#include "GLOBAL.h"

class Enemy
{
protected:
	int e_HP;
	char e_xPos;
	char e_yPos;

	char goto_xPos;
	char goto_yPos;

	bool isActive;

	unsigned char BulletPos;

	char _InherenceIndex;
	const char ID;
	const char Enemy_LV_ID;

	Bullet* EnemyBullet[100];

public:

	Enemy(const char _id, const int _HP, const char Enemy_LV_ID);

	void InitEnemy();

	void Shoot(const char Enemy_LV_ID);

	bool CheckCrash(const int _TargetX, const int _TargetY, int TargetSize = 2);

	void GetDamage(int _damage);

	void MoveToXY(const int _x, const int _y, Enemy* EnemyLV[]);

	bool f_isActive();

	void DisplayEnemy(const char Enemy_LV_ID);

	const char GetEnemyID();

	~Enemy();
};

