#include "stdafx.h"
#include "cabbage.h"
#include "abc.h"

bool cabbage::life(int tic) const
{
	if (tic == 0)
		return false;
	else 
		if (((tic - birthday) % life_day) == 0)
			return true;
	    else
			return false;
}

bool cabbage::reproduction(int tic) const
{
	if (tic == 0)
		return false;
	else
		if (((tic - birthday) % reproduction_day) == 0)
			return true;
		else
		    return false;
}

void cabbage::movement()
{
	int rand_x = 0, rand_y = 0;
	while ((rand_x == 0) & (rand_y == 0))
	{
		rand_x = rand() % 3 - 1;
	    rand_y = rand() % 3 - 1;
	}
	x += rand_x;
	y += rand_y;
}
