#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <windows.h> 
#include <time.h>
using namespace std;

#include "Player.h"

/*
* 
	int p_Hp;
	int p_Attack;
	int p_Defense;
	int p_Speed;
	int p_BulletSpeed;

	//Player Pos Info
	int xPos;
	int yPos;

	Bullet* p_Bullet[100];

*/

Player::Player(const int _xPos, const int _yPos, const int _p_Hp) : xPos(_xPos), yPos(_yPos), p_Hp(_p_Hp){}

int Player::GetXPos()
{
	return xPos;
}

int Player::GetYPos()
{
	return yPos;
}

int Player::GetHP()
{
	return p_Hp;
}

void Player::CaclXPos(const int _val)
{
	xPos += _val;
}

void Player::CaclYPos(const int _val)
{
	yPos += _val;
}

void Player::SetXPos(const int _val)
{
	xPos = _val;
}

void Player::SetYPos(const int _val)
{
	yPos = _val;
}

bool Player::Player_isDead()
{
	return Player::p_Hp <= 0;
}

bool Player::Player_Move()
{
	
	drawToBackBuffer(xPos - 3, yPos - 1, "- o0o -");
	drawToBackBuffer(xPos - 1, yPos, "_|_");

	return true;
}

bool Player::CheckCrash(int _TargetX, int _TargetY, int TargetSize)
{
	return (xPos - TargetSize <= _TargetX && xPos + TargetSize >= _TargetX)
		&& (yPos - TargetSize <= _TargetY && yPos + TargetSize >= _TargetY);
}

void Player::GetDamage(int _damage)
{
	p_Hp -= _damage;
	if (p_Hp <= 0) system("pause");
}