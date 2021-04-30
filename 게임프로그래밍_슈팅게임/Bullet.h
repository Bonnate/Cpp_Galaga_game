#pragma once

class Enemy;
class Player;
#include "Enemy.h"

class Bullet
{
protected:
	int b_xPos;
	int b_yPos;
	int b_Damage;
	bool isActive;

public:
	Bullet();

	void UseBullet_To_Enemy(Enemy* enemyClass[]);

	void Bullet_To_Player(Player* PlayerClass, const char EnemyLVID);

	void RemoveBullet();

	void InitBullet(int xPos, int yPos);

	bool f_isActive();

	void f_setActive(bool _flag);

};