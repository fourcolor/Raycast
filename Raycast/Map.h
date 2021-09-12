#pragma once
#include <string>
#include <vector>
using namespace std;
class Map
{
public:
	Map();
	bool collision(int, int);
	int getWidth();
	int getHeight();
	string getMap();
private:
	int width, height;
	string map;
};

