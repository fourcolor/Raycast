#include "Screen.h"
Screen::Screen(int x, int y)
{
	this->height = y;
	this->width = x;
	this->screen = new wchar_t[x * y];
}
int Screen::getHeight()
{
	return this->height;
}

int Screen::getWidth()
{
	return this->width;
}

void Screen::set(int x, int y, wchar_t c)
{
	this->screen[y * this->width + x] = c;
}

wchar_t* Screen::getScreen()
{
	return this->screen;
}