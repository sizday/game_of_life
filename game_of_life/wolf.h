#pragma once
#include "abc.h"
#include <iostream>
#include "stdafx.h"
class wolf : public abc
{
public:
	wolf(int birth = 0) : x(rand() % 40), y(rand() % 60), birthday(birth) {}
	wolf(int x_cur, int y_cur, int birth = 0) : x(x_cur), y(y_cur), birthday(birth) {}
	virtual ~wolf() {}
	virtual bool life(int tic) const;
	virtual bool reproduction(int tic) const;
	virtual int GetX() { return x; }
	virtual int GetY() { return y; }
	virtual int GetBirth() { return birthday; }
	virtual int GetAnim() { return 3; }
	virtual void movement();
	virtual void moveR() { x += 1; }
	virtual void moveL() { x -= 1; }
	virtual void moveH() { y += 1; }
	virtual void moveD() { y -= 1; }
private:
	int x;
	int y;
	int birthday;
	const int life_day = 24;
	const int reproduction_day = 5;
};

