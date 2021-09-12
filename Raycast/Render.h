#pragma once
#include "Player.h"
#include "Screen.h"
#include "Map.h"
#include <Windows.h>

class Render
{
public:
	const wchar_t pixel[5] = { '#','x','.','-',' ' };
	void render(Player*, Map*, Screen*, float, HANDLE&);
private:
	void showStatus(Screen*, Player*, float);
	void showMap(Screen*, Map*, Player*);
	void show(HANDLE&, Screen*);
};

