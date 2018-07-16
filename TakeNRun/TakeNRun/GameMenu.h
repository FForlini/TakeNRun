#include <iostream>
#include <glut.h>
#include <gl\GL.h>
#pragma once

using namespace std;

class GameMenu
{
private:
int widthL;
int heightL;
GLboolean selectedl1;                   //enable the selection of a button
GLboolean selectedl2;                   //enable the selection of a button
string buttonl1;
string buttonw1;
string buttonl2;
public:	
	GameMenu(int w,int h);
	~GameMenu(void);
	GLboolean retry;
	GLboolean win;
	GLboolean continuew;
	GLuint getTexture(string);
	void write(string ,void *font ,float ,float );
	void drawButton(string ,float,float ,GLboolean );
	void onMouseMove(int ,int );
	void draw(GLuint,bool,int);
	bool onMouseClick(int,int ,int ,int );
	void write(string,int,void* ,float,float);
};

