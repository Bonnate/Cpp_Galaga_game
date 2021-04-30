#pragma once

class Bullet;

#include "Bullet.h"
#include "GLOBAL.h"

class Player
{
private:
	int p_Hp;
	int p_Attack;
	int p_Defense;
	int p_Speed;
	int p_BulletSpeed;	

	//Player Pos Info
	int xPos;
	int yPos;


	Bullet* p_Bullet[100];

public:
	Player(const int _xPos, const int _yPos, const int _p_Hp);

	//Return Player Pos Info
	int GetXPos();
	int GetYPos();
	int GetHP();

	//Cacl Player Pos Info
	void CaclXPos(const int _val);
	void CaclYPos(const int _val);

	//Set Player Pos Info
	void SetXPos(const int _val);
	void SetYPos(const int _val);

	//Player Func
	bool Player_isDead();
	bool Player_Move();

	bool CheckCrash(int _TargetX, int _TargetY, int TargetSize);

	void GetDamage(int _damage);
	
};


