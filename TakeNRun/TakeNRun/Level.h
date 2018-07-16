#pragma once
class Level
{
private:

int speed;
int nTnt;
int nSkull;
int level;
int diff;

public:
	Level(int,int);
	virtual ~Level(void);
	int getSpeed();
	int getNTnt();
	int getNSkull();
	int getLevel();
	int getNum();
	int getDiff();
};

