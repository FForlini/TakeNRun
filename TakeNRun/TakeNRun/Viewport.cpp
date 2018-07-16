#include "Viewport.h"
#include <iostream>
#include <string.h>
#include <glut.h>
#include <Gl/gl.h>
#include <SOIL.h>

using namespace std;

float xv,len,yv,he;                      //variabili per la creazione di una viewport con le informazioni sul livello
int scoreG,lev,lvs,totalScore;           //variabili per tener traccia del punteggio-livello-vite-punteggio totale

/*
Costruttore per settare tutte le variabili ai valori iniziali
*/
Viewport::Viewport(float x,float y,float w,float h,int lvs)
{
	xv=x;
	yv=y;
	len=w;
	he=h;
	this->lvs = lvs;
	scoreG = 47;
}
/*
Distruttore virtuale
*/
Viewport::~Viewport(void)
{
}
/*
Setta i valori predefiniti del livello
*/
void Viewport::setScoreNLevel(int totsc,int lv)         
{
	scoreG++;
	lev = lv+48;
	totalScore = totsc;
}
/*
Metodo per la scrittura di testo sulla viewport
*/
void Viewport::write(string s,int num,void *font ,float x,float y){          
	glPushMatrix();
	glRasterPos2f(x,y);

	for(int i=0; i < s.length(); i++){             
		if(s[i]=='\n')
			glutBitmapCharacter(font, 0);        
		else
		glutBitmapCharacter(font, (int) s[i]);
	}
	glutBitmapCharacter(font, num);
	glPopMatrix();
}
/*
Disegna le texture delle vite
*/
void Viewport::drawLives(GLfloat x, GLfloat y,GLuint texture){        
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
	// FRONT
	glTexCoord2f(0,0);
	glVertex2f(x+20,y);
	glTexCoord2f(1,0);
	glVertex2f(x,y);
	glTexCoord2f(1,1);
	glVertex2f(x,y+20);
	glTexCoord2f(0,1);
	glVertex2f(x+20,y+20);
		
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
/*
Disegna il contenuto della viewport
*/
void Viewport::drawVS(GLuint texture)
{
	glViewport(xv,yv,len,he);
	glMatrixMode(GL_PROJECTION);          
	glLoadIdentity();
	gluOrtho2D(-100.f,100.f,-100.*he/len,100.*he/len);
	glColor3f(1,1,1);
	write("Livello:  ",lev,GLUT_BITMAP_8_BY_13,-20,0);
	if(scoreG-48 < 10)
	 write("Punteggio livello:  ",scoreG,GLUT_BITMAP_8_BY_13,-20,-30);
	else
	{
		write("Punteggio livello:  ",(scoreG-48)/10 +48,GLUT_BITMAP_8_BY_13,-20,-30);
		write("",(scoreG-48) % 10 +48,GLUT_BITMAP_8_BY_13,85,-30);
	}
	if(totalScore < 10)
	 write("Punteggio totale:   ",totalScore+48,GLUT_BITMAP_8_BY_13,-20,-60);
	else
	{
		write("Punteggio livello:  ",(totalScore)/10 +48,GLUT_BITMAP_8_BY_13,-20,-60);
		write("",(totalScore) % 10 +48,GLUT_BITMAP_8_BY_13,85,-60);
	}
		
	switch(lvs)                                            //distinzione del numero di vite a disposizione
	{
	  case 1: drawLives(-20,20,texture);
		  break;
	  case 2: drawLives(-20,20,texture);
			  drawLives(10,20,texture);
			 break;
	  case 3: drawLives(-20,20,texture);
			  drawLives(10,20,texture);
		      drawLives(40,20,texture);
		   break;
	  case 4: drawLives(-20,20,texture);
			  drawLives(10,20,texture);
		      drawLives(40,20,texture);
		      drawLives(70,20,texture);
		  break;

	  default: break;
	}

	
}
/*
Setta il numero delle vite per aggiornare la viewport
*/
void Viewport::setLives(int lvs)
{
	this->lvs = lvs;
}
