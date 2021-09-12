#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Player.h"
#include "Map.h"
#include <algorithm>
#include "Render.h"
#include "Screen.h"
using namespace std;

//視窗大小
int screenWidth = 120;			
int screenHeight = 40;	

//人物資訊
float playerX = 14.7f;			
float playerY = 5.09f;
float playerA = 0.0f;			
float playerFOV = 3.14159f / 4.0f;
float playerSightDepth = 16.0f;
float playerSpeed = 2.0f;

auto t1 = chrono::system_clock::now();
auto t2 = chrono::system_clock::now();

int main()
{
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	Screen *screen = new Screen(screenWidth, screenHeight);
	Map* map = new Map();
	Render* render = new Render();
	Player* player = new Player(playerX, playerY, playerA, playerSpeed, playerFOV, playerSightDepth);

	while (1)
	{
		t2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = t2 - t1;
		t1 = t2;
		float dTimet = elapsedTime.count();
		player->move(dTimet, *map);
		render->render(player, map, screen,dTimet, hConsole);
	}
}

