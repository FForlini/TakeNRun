#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <gl\GL.h>
#include <Windows.h>
#include "Coordinate.h"
#include "Level.h"

#pragma once
class Game
{
private:

int x2d,y2d;


float angle;

int mainW;

int matrix[20][20];
float fraction;

float cx,cy,cz;
float dirx,diry,dirz;
float angleY;

bool lost,won,isInPause;

public:
	Game(int,int,Level*);
	virtual ~Game(void);
	void drawPieces(int [20][20]);
	void returnToMatrix();
	void timerFunction();
	void initTexture();
	void drawCube(GLfloat,GLfloat, GLfloat,GLfloat,char);
	void drawRect(Coordinate* c1);
	void drawFoodPos(GLfloat x,GLfloat y,GLfloat z);
	void draw();
	void keyboard(unsigned char , int , int );
	void idle();
	GLuint getTexture(std::string);
	void drawWall();
	void draw2DField();
	void drawFood(GLfloat,GLfloat);
	void mouseMoveFunc(int,int);
	bool mouseClickFunc(int ,int ,int ,int );
	void reset();
	void setLevel(Level*);
};

