#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <windows.h> 
#include <time.h>
using namespace std;
int GetMAX_PLAYERS();
void render();

#include "DeviceCtl.h"

bool StartProgram()
{
	bool GAMESTART = FALSE;
	bool is1Player = TRUE;
	while (1)
	{
		drawToBackBuffer(20, 10, " _______   _______   ___       ___      _______     ______     _______");
		drawToBackBuffer(20, 11, "|       | |   _   | |   |     |   |     |       |  |    _ |   |       |");
		drawToBackBuffer(20, 12, "|    ___| |  |_|  | |   |     |   |     |    ___|  |   | ||   |    ___|");
		drawToBackBuffer(20, 13, "|   |  __ |       | |   |     |   |     |   |___   |   | ||_  |   | __");
		drawToBackBuffer(20, 14, "|   | | | |       | |   |___  |   |___  |    ___|  |    __  | |   | | |");
		drawToBackBuffer(20, 15, "|   |_| | |   _   | |       | |       | |   |___   |   |  | | |   |_| |");
		drawToBackBuffer(20, 16, "|_______| |__| |__| |_______| |_______| | _______| |___|  |_| |_______|");
		drawToBackBuffer(35, 17, " _______   _______   __   __   _______");
		drawToBackBuffer(35, 18, "|       | |   _   | |  |_|  | |       |");
		drawToBackBuffer(35, 19, "|    ___| |  |_|  | |       | |    ___|");
		drawToBackBuffer(35, 20, "|   |  __ |       | |       | |   |___");
		drawToBackBuffer(35, 21, "|   | | | |       | |       | |    ___|");
		drawToBackBuffer(35, 22, "|   |_| | |   _   | | ||_|| | |   |___");
		drawToBackBuffer(35, 23, "|_______| |__| |__| |_|   |_| |_______|");

		drawToBackBuffer(30, 50, " ___    _____  _           __     ________ _____");
		drawToBackBuffer(30, 51, "|__ \\  |  __ \\| |        /\\\\ \\   / /  ____| __  \\");
		drawToBackBuffer(30, 52, "   ) | | |__) | |       /  \\\\ \\_/ /| |__  | |__)|");
		drawToBackBuffer(30, 53, "  / /  |  ___/| |      / /\\ \\\\   / |  __| |  _  /");
		drawToBackBuffer(30, 54, " / /_  | |    | |____ / ____ \\| |  | |____| | \\ \\");
		drawToBackBuffer(30, 55, "|____| |_|    |______/_/    \\_\\_|  |______|_|  \\_\\");

		drawToBackBuffer(30, 58, "  __    _____  _           __     ________ _____");
		drawToBackBuffer(30, 59, " /_ |  |  __ \\| |        /\\\\ \\   / /  ____| __  \\");
		drawToBackBuffer(30, 60, "  | |  | |__) | |       /  \\\\ \\_/ /| |__  | |__)|");
		drawToBackBuffer(30, 61, "  | |  |  ___/| |      / /\\ \\\\   / |  __| |  _  /");
		drawToBackBuffer(30, 62, "  | |  | |    | |____ / ____ \\| |  | |____| | \\ \\");
		drawToBackBuffer(30, 63, "  |_|  |_|    |______/_/    \\_\\_|  |______|_|  \\_\\");



		if (GetAsyncKeyState(VK_UP) & 0x8000)			is1Player = FALSE;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)			is1Player = TRUE;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)		return is1Player;

		if (is1Player)
		{
			drawToBackBuffer(20, 58, "	   __	 ");
			drawToBackBuffer(20, 59, "	   \\ \\	 ");
			drawToBackBuffer(20, 60, " ____\\ \\	 ");
			drawToBackBuffer(20, 61, "|_____  > ");
			drawToBackBuffer(20, 62, "	    / /	 ");
			drawToBackBuffer(20, 63, "	   /_/	 ");

		}
		else
		{
			drawToBackBuffer(20, 50, "	   __	 ");
			drawToBackBuffer(20, 51, "	   \\ \\	 ");
			drawToBackBuffer(20, 52, " ____\\ \\	 ");
			drawToBackBuffer(20, 53, "|_____  > ");
			drawToBackBuffer(20, 54, "	    / /	 ");
			drawToBackBuffer(20, 55, "	   /_/	 ");
		}

		render();
	}
}

void DisplayInfo(const int Player_1_HP)
{
	int i = 0;
	for (; i < 62; ++i)
	{
		drawToBackBuffer(80, i, "|");
	}

	for (int j = 80; j < 110; ++j)
	{
		drawToBackBuffer(j, i, "_");
	}

	for (; i < 70; ++i)
	{
		drawToBackBuffer(80, i, "|");
	}

	drawToBackBuffer(82, 64, "OO  OO OOOOOO");
	drawToBackBuffer(82, 65, "OO  OO OO  OO");
	drawToBackBuffer(82, 66, "OOOOOO OOOOOO");
	drawToBackBuffer(82, 67, "OO  OO OO");
	drawToBackBuffer(82, 68, "OO  OO OO");

	switch (Player_1_HP)
	{
	case 4:
		drawToBackBuffer(102, 64, "OO  OO");
		drawToBackBuffer(102, 65, "OO  OO");
		drawToBackBuffer(102, 66, "OOOOOO");
		drawToBackBuffer(102, 67, "    OO");
		drawToBackBuffer(102, 68, "    OO");
		return;

	case 3:
		drawToBackBuffer(102, 64, "OOOOOO");
		drawToBackBuffer(102, 65, "    OO");
		drawToBackBuffer(102, 66, "OOOOOO");
		drawToBackBuffer(102, 67, "    OO");
		drawToBackBuffer(102, 68, "OOOOOO");
		return;

	case 2:
		drawToBackBuffer(102, 64, "OOOOOO");
		drawToBackBuffer(102, 65, "    OO");
		drawToBackBuffer(102, 66, "OOOOOO");
		drawToBackBuffer(102, 67, "00");
		drawToBackBuffer(102, 68, "OOOOOO");
		return;

	case 1:
		drawToBackBuffer(102, 64, "OOOO");
		drawToBackBuffer(102, 65, "  OO");
		drawToBackBuffer(102, 66, "  OO");
		drawToBackBuffer(102, 67, "  OO");
		drawToBackBuffer(102, 68, "OOOOOO");
		return;
	}
}


void DisplayInfo(const int Player_1_HP, const int Player_2_HP)
{
	int i = 0;
	for (; i < 56; ++i)
	{
		drawToBackBuffer(80, i, "|");
	}

	for (int j = 80; j < 110; ++j)
	{
		drawToBackBuffer(j, i, "_");
	}

	for (; i < 70; ++i)
	{
		drawToBackBuffer(80, i, "|");
	}



	drawToBackBuffer(82, 58, "OO  OO OOOOOO");
	drawToBackBuffer(82, 59, "OO  OO OO  OO");
	drawToBackBuffer(82, 60, "OOOOOO OOOOOO");
	drawToBackBuffer(82, 61, "OO  OO OO");
	drawToBackBuffer(82, 62, "OO  OO OO   1");

	drawToBackBuffer(82, 64, "OO  OO OOOOOO");
	drawToBackBuffer(82, 65, "OO  OO OO  OO");
	drawToBackBuffer(82, 66, "OOOOOO OOOOOO");
	drawToBackBuffer(82, 67, "OO  OO OO");
	drawToBackBuffer(82, 68, "OO  OO OO   2");

	switch (Player_1_HP)
	{
	case 4:
		drawToBackBuffer(102, 58, "OO  OO");
		drawToBackBuffer(102, 59, "OO  OO");
		drawToBackBuffer(102, 60, "OOOOOO");
		drawToBackBuffer(102, 61, "    OO");
		drawToBackBuffer(102, 62, "    OO");
		break;

	case 3:
		drawToBackBuffer(102, 58, "OOOOOO");
		drawToBackBuffer(102, 59, "    OO");
		drawToBackBuffer(102, 60, "OOOOOO");
		drawToBackBuffer(102, 61, "    OO");
		drawToBackBuffer(102, 62, "OOOOOO");
		break;

	case 2:
		drawToBackBuffer(102, 58, "OOOOOO");
		drawToBackBuffer(102, 59, "    OO");
		drawToBackBuffer(102, 60, "OOOOOO");
		drawToBackBuffer(102, 61, "00");
		drawToBackBuffer(102, 62, "OOOOOO");
		break;

	case 1:
		drawToBackBuffer(102, 58, "OOOO");
		drawToBackBuffer(102, 59, "  OO");
		drawToBackBuffer(102, 60, "  OO");
		drawToBackBuffer(102, 61, "  OO");
		drawToBackBuffer(102, 62, "OOOOOO");
		break;
	}
	switch (Player_2_HP)
	{
	case 4:
		drawToBackBuffer(102, 64, "OO  OO");
		drawToBackBuffer(102, 65, "OO  OO");
		drawToBackBuffer(102, 66, "OOOOOO");
		drawToBackBuffer(102, 67, "    OO");
		drawToBackBuffer(102, 68, "    OO");
		return;

	case 3:
		drawToBackBuffer(102, 64, "OOOOOO");
		drawToBackBuffer(102, 65, "    OO");
		drawToBackBuffer(102, 66, "OOOOOO");
		drawToBackBuffer(102, 67, "    OO");
		drawToBackBuffer(102, 68, "OOOOOO");
		return;

	case 2:
		drawToBackBuffer(102, 64, "OOOOOO");
		drawToBackBuffer(102, 65, "    OO");
		drawToBackBuffer(102, 66, "OOOOOO");
		drawToBackBuffer(102, 67, "00");
		drawToBackBuffer(102, 68, "OOOOOO");
		return;

	case 1:
		drawToBackBuffer(102, 64, "OOOO");
		drawToBackBuffer(102, 65, "  OO");
		drawToBackBuffer(102, 66, "  OO");
		drawToBackBuffer(102, 67, "  OO");
		drawToBackBuffer(102, 68, "OOOOOO");
		return;
	}
}