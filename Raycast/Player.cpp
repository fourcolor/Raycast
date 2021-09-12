#include "Map.h"
#include "Player.h"
#include <Windows.h>
#include <algorithm>
Player::Player(float x, float y, float a, float s, float f, float sight)
{
	this->x = x;
	this->y = y;
	this->angle = a;
	this->speed = s;
	this->fov = f;
	this->sightDepth = sight;
}

void Player:: move(float time, Map map) {
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		this->angle -= (this->speed * 0.75f) * time;

	//向右轉
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		this->angle += (this->speed * 0.75f) * time;

	//向前走
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
	{
		int preX = this->x + sinf(this->angle) * this->speed;
		int preY = this->y + cosf(this->angle) * this->speed;
		if (!map.collision(preX, preY))
		{
			this->x = preX;
			this->y = preY;
		}
	}

	//向後走
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
	{
		int preX = this->x - sinf(this->angle) * this->speed;
		int preY = this->y - cosf(this->angle) * this->speed;
		if (!map.collision(preX, preY))
		{
			this->x = preX;
			this->y = preY;
		}
	}
}

float Player::getX()
{
	return this->x;
}

float Player::getY()
{
	return this->y;
}

float Player::getAngle()
{
	return this->angle;
}

float Player::getSightDepth()
{
	return this->sightDepth;
}

float Player::getFOV()
{
	return this->fov;
}