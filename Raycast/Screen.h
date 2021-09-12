#pragma once
class Screen
{
public :
	Screen(int, int);
	int getWidth();
	int getHeight();
	void set(int, int, wchar_t);
	wchar_t* getScreen();
private:
	int width, height;
	wchar_t* screen;
};

