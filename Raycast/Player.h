#ifndef _Player_H_
#define  _Player_H_
#include "Map.h"
class Player
{
public:
	Player(float, float, float, float, float, float);
	void move(float, Map);
	float getX();
	float getY();
	float getAngle();
	float getSpeed();
	float getFOV();
	float getSightDepth();
private:
	float x, y, angle, speed, fov, sightDepth;
};
#endif



