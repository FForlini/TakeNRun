#include "Coordinate.h"
#pragma once



class Enemy
{
private:
	Coordinate* posEnemy;

	int contX,contY;

	bool dctx,dcty;

	char type;
public:
	Enemy(char);
	Enemy(Coordinate*,char);
	virtual ~Enemy(void);
	void updatePosition(int,int);
	Coordinate* getCoord();
	void AI(int);
	
	char getType();
	void level3(int,int,int);
	void level1_2(int,int,int);

};

