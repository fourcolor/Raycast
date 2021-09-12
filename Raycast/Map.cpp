#include "Map.h"
#include <fstream>
Map::Map() {
	ifstream file;
	file.open("Map.txt",ios::in);
	if (file)
	{
		char buffer[100] = { '\0' };
		file.getline(buffer, 3);
		this->height = atoi(buffer);
		file.getline(buffer, 3);
		this->width= atoi(buffer);
		for (int i = 0; i < this->height; i++)
		{
			file.getline(buffer, 100);
			this->map += atoi(buffer);
		}
	}
	else
	{
		this->height = 16;
		this->width = 16;
		this->map += "################";
		this->map += "#..............#";
		this->map += "#.......########";
		this->map += "#..............#";
		this->map += "#......##......#";
		this->map += "#......##......#";
		this->map += "#..............#";
		this->map += "###............#";
		this->map += "##.............#";
		this->map += "#......####..###";
		this->map += "#......#.......#";
		this->map += "#......#.......#";
		this->map += "#..............#";
		this->map += "#......#########";
		this->map += "#..............#";
		this->map += "################";
	}
}

bool Map::collision(int x, int y) {
	if ( this->map[x * this->width + y] == '#')
	{
		return true;
	}
	return false;
}

int Map::getWidth()
{
	return this->width;
}

int Map::getHeight()
{
	return this->height;
}

string Map::getMap()
{
	return this->map;
}