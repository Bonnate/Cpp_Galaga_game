#pragma once

extern int MAX_PLAYERS;
constexpr int PLAYERMAXBULLET = 10;
constexpr int ENEMYLV_1MAXBULLET = 2;
constexpr int ENEMYLV_2MAXBULLET = 5;
constexpr int ENEMYLV_1MAXCNT = 8;
constexpr int ENEMYLV_2MAXCNT = 5;

void drawToBackBuffer(const int i, const int j, const char* image);

void textcolor(int foreground, int background);