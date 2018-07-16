#include <iostream>
#include <glut.h>
#include <gl\GL.h>
#include <SOIL.h>
#include <irrKlang.h>
#include "GameMenu.h"
#include "Game.h"

using namespace std;  

irrklang::ISoundEngine* engineL ;

GLboolean selectedl1,selectedl2;              //booleani per la selezione dei bottoni     
GLboolean retry,continuew,win;            
string buttonw1,buttonl2;                     //stringhe per i bottoni

int widthL,heightL;
GLuint youLose;

/*
Costruttore per settare tutte le variabili al valore iniziale
*/
GameMenu::GameMenu(int w,int h)
{
	widthL=w;
	heightL=h;
	selectedl1=false;
	selectedl2=false;
	retry=false;
	continuew=false;
	win=false;
	buttonl1="Rientra";
	buttonw1= "Continua";
	buttonl2="Esci";

	engineL = irrklang::createIrrKlangDevice();    //create an audio engine
}
/*
Distruttore virtuale
*/
GameMenu::~GameMenu(void)
{
}

/*
Metodo per scrivere il testo semplice
*/
void GameMenu::write(string s,void *font ,float x,float y){                  

	glRasterPos2f(x,y);	  
	for(int i=0; i<s.length(); i++){             //scrive il testo
		if(s[i]=='\n')
			glutBitmapCharacter(font, 0);        //se è un terminatore di stringa non scrive nulla
		else
		glutBitmapCharacter(font, (int) s[i]);
	}
	
}
/*
Metodo per scrivere il punteggio
*/
void GameMenu::write(string s,int num,void *font ,float x,float y){            
	glPushMatrix();
	glRasterPos2f(x,y);

	for(int i=0; i < s.length(); i++){             //draw the text
		if(s[i]=='\n')
			glutBitmapCharacter(font, 0);        //if the character is a string terminator,don't write anything
		else
		glutBitmapCharacter(font, (int) s[i]);
	}
	glutBitmapCharacter(font, num);
	glPopMatrix();
}
/*
Metodo drawButton del tutto simile a quello del menu principale
*/
void GameMenu::drawButton(string s,float x,float y,GLboolean selected){        
	if(selected)
	glColor3f(0,0,0);                         

	write(s,GLUT_BITMAP_9_BY_15,x+0.15,y+0.1);

	glColor3f(1.0,0.3,0.1);

	if(selected)
	glPolygonMode(GL_FRONT, GL_FILL);      
	else
	glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_QUADS);                          
	glVertex2f(x,y);
	glVertex2f(x+0.5,y);
	glVertex2f(x+0.5,y+0.2);
	glVertex2f(x,y+0.2);
	glEnd();

}
/*
Disegna i pulsanti e la texture del titolo del menu
*/
void GameMenu::draw(GLuint texture,bool win,int scoreG)
{
	float x=-0.5;
	float y=0.4;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_COLOR);
	glLoadIdentity();

	glViewport( 0,0, widthL, heightL );
	
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
	glVertex2f(x+1,y);
	glTexCoord2f(1,0);
	glVertex2f(x,y);
	glTexCoord2f(1,1);
	glVertex2f(x,y+0.3);
	glTexCoord2f(0,1);
	glVertex2f(x+1,y+0.3);
		
	glEnd();
	glDisable(GL_TEXTURE_2D);

	if(!win){
	drawButton(buttonl1,-0.25,0,selectedl1);
	drawButton(buttonl2,-0.25,-0.4,selectedl2);	
	}
	else{
	drawButton(buttonw1,-0.25,0,selectedl1);
	drawButton(buttonl2,-0.25,-0.4,selectedl2);	
	}

	glColor3f(0,1,0);
	write("Punteggio totale:  ",scoreG/10 +48,GLUT_BITMAP_8_BY_13,-0.25,-0.7);
	write("",(scoreG) % 10 +48,GLUT_BITMAP_8_BY_13,0.25,-0.7);
	glutPostRedisplay();
	glColor3f(1.0,0.3,0.1);

	glutSwapBuffers();
}
/*
Gestisce il movimento del mouse
*/
void GameMenu::onMouseMove(int xMouse,int yMouse){
	
	float k = 1.0;                               //scale factor

	if(widthL==800)
		k=1.25; 

	if(xMouse<399*k && xMouse>240*k && yMouse<239*k && yMouse>193*k)         //RETRY
		selectedl1=true;
	else
		selectedl1=false;

	if(xMouse<399*k && xMouse>240*k && yMouse<335*k && yMouse>288*k)         //EXIT
		selectedl2=true;
	else
		selectedl2=false;

	glutPostRedisplay();
}
/*
Gestisce il click del mouse
*/
bool GameMenu::onMouseClick(int button,int state,int xMouse,int yMouse){

	float k = 1.0;     	//fattore di scala

	if(widthL==800)
		k=1.25;     

	if(xMouse<399*k && xMouse>240*k && yMouse<239*k && yMouse>193*k && state==GLUT_DOWN){         //RETRY
		engineL->play2D("Tick.mp3",false);
		return true;
	}


	if(xMouse<399*k && xMouse>240*k && yMouse<335*k && yMouse>288*k){         //EXIT
	      engineL->play2D("Tick.mp3",false);
		  exit(0);
	}
	return false;
	glutPostRedisplay();
}