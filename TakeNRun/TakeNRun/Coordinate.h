#pragma once
class Coordinate
{
private:
  float x;
  float y;

public:
	Coordinate();
	Coordinate(float,float);
	virtual ~Coordinate(void);
	float getX();
	float getY();
	void setX(float);
	void setY(float);
};

