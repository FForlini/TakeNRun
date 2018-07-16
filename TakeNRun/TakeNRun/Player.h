#include "Coordinate.h"
#pragma once

class Player
{

private:
	float cameraX,cameraY,cameraZ;
	float dirX,dirY,dirZ;
	float angle;
public:
	Player(Coordinate*);
	virtual ~Player(void);
	void setPlayerPos(Coordinate* );
	float getXCam();
	float getYCam();
	float getZCam();
	void setZCam(float);
	void setYCam(float);
	void setXCam(float);
	void goStraight(float);
	void goBack(float);
	void turnLeft();
	void turnRight();
	float getDirX();
	float getDirY();
	float getDirZ();
	void up(float);
	void down(float);
	void left();
	void right();
	float getX2D();
	float getY2D();
	void setX2D(float);
	void setY2D(float);
};

