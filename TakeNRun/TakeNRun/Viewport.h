#pragma once
#include <iostream>
#include <string.h>
#include <glut.h>
#include <Gl/gl.h>
#include <SOIL.h>

using namespace std;

class Viewport
{
private:
	float xv,len;
    float yv,he;	
	int lvs;
	int scoreG,lev;      
public:	
	Viewport(float ,float ,float ,float,int);
	~Viewport(void);
	void write(string ,int,void *font ,float ,float );
	void drawVS(GLuint);
	void setLives(int);
	void drawLives(GLfloat , GLfloat, GLuint);
	void setScoreNLevel(int,int);
};
