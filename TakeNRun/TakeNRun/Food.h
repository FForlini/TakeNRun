#include "Coordinate.h"
#pragma once
class Food
{
private:
	Coordinate* pos;

public:
	Food();
	Food(Coordinate*);
	virtual ~Food(void);
    Coordinate* getPos();
};

