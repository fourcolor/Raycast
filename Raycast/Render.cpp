#include "Render.h"
#include "Player.h"
#include "Screen.h"
#include "Map.h"
#include <algorithm>

void Render::render(Player* player, Map* map, Screen* screen, float dTime, HANDLE& hconsloe) {
	for (int x = 0; x < screen->getWidth(); x++)
	{
		float rayAngle = (player->getAngle() - player->getFOV() / 2.0f) + ((float)x / (float)screen->getWidth()) * player->getFOV();

		//用來找到牆的距離
		float fStepSize = 0.1f;
		//解析度
		float fDistanceToWall = 0.0f; 
		//ray偵測撞牆
		bool hitWall = false;		
		//ray偵測邊界
		bool boundary = false;		

		//ray單位角度
		float rayX = sinf(rayAngle);
		float rayY = cosf(rayAngle);


		while (!hitWall && fDistanceToWall < player->getSightDepth())
		{
			fDistanceToWall += fStepSize;
			int nTestX = (int)(player->getX() + rayX * fDistanceToWall);
			int nTestY = (int)(player->getY() + rayY * fDistanceToWall);

			//偵測邊界
			if (nTestX < 0 || nTestX >= map->getWidth() || nTestY < 0 || nTestY >= map->getHeight())
			{
				hitWall = true;			
				fDistanceToWall = player->getSightDepth();
			}
			else
			{
				if (map->collision(nTestX, nTestY))
				{
					hitWall = true;

					// 偵測牆的轉角，存距離及對rayX,rayY的內積
					vector<pair<float, float>> p;
					for (int tx = 0; tx < 2; tx++)
						for (int ty = 0; ty < 2; ty++)
						{
							// Angle of corner to eye
							float vy = (float)nTestY + ty - player->getY();
							float vx = (float)nTestX + tx - player->getX();
							float d = sqrt(vx * vx + vy * vy);
							float dot = (rayX * vx / d) + (rayY * vy / d);
							p.push_back(make_pair(d, dot));
						}

					// 由近到遠排序
					sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; });

					float bound = 0.01;
					if (acos(p.at(0).second) < bound) boundary = true;
					if (acos(p.at(1).second) < bound) boundary = true;
					if (acos(p.at(2).second) < bound) boundary = true;
				}
			}
		}


		//計算高度及地板
		int nCeiling = (float)(screen->getHeight() / 2.0) - screen->getHeight() / ((float)fDistanceToWall);
		int nFloor = screen->getHeight() - nCeiling;

		// 牆的高度會跟距離有關
		short shade = ' ';
		if (fDistanceToWall <= screen->getWidth() / 4.0f)
		{
			//近
			shade = 0x2588;	
		}
		else if (fDistanceToWall < player->getSightDepth() / 3.0f)
		{
			shade = 0x2593;
		}
		else if (fDistanceToWall < player->getSightDepth() / 2.0f)
		{ 
			shade = 0x2592; 
		}
		else if (fDistanceToWall < player->getSightDepth()) 
		{ 
			shade = 0x2591; 
		}
		else
		{
			//遠
			shade = this->pixel[4];
		}

		if (boundary)
		{
			shade = this->pixel[4];
		}

		for (int y = 0; y < screen->getHeight(); y++)
		{
			if (y <= nCeiling)
				screen->set(x, y, this->pixel[4]);
			else if (y > nCeiling && y <= nFloor)
				screen->set(x, y, shade);
			else
			{
				float b = 1.0f - (((float)y - screen->getHeight() / 2.0f) / ((float)screen->getHeight() / 2.0f));
				if (b < 0.25)
				{
					shade = this->pixel[0];
				}
				else if (b < 0.5)
				{
					shade = this->pixel[1];
				}
				else if (b < 0.75)
				{
					shade = this->pixel[2];
				}
				else if (b < 0.9)
				{
					shade = this->pixel[3];
				}
				else
				{
					shade = this->pixel[4];
				}
				screen->set(x, y, shade);
			}
		}
	}
	this->showStatus(screen,player,dTime);
	this->showMap(screen,map,player);
	this->show(hconsloe,screen);
}

void Render::showStatus(Screen* screen ,Player* player, float t)
{
	swprintf_s(screen->getScreen(), 100, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f\0 ", player->getX(), player->getY(), player->getAngle(), 1.0f / t);
}
void Render::showMap(Screen* screen, Map* map, Player* player) 
{
	for (int nx = 0; nx < map->getWidth(); nx++)
		for (int ny = 0; ny < map->getWidth(); ny++)
		{
			screen->set(nx,ny+1,map->getMap()[ny * map->getWidth() + nx]);
		}
	screen->set((int)player->getY(), ((int)player->getX() + 1),'P');
}
void Render::show(HANDLE& hConsole, Screen* screen)
{
	DWORD dwBytesWritten = 0;
	screen->set(-1, screen->getHeight(),'\0');//screen的最後一位
	WriteConsoleOutputCharacter(hConsole, screen->getScreen(), screen->getWidth() * screen->getHeight(), { 0,0 }, &dwBytesWritten);
}