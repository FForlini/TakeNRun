#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <gl\GL.h>
#include <Windows.h>
#include <irrKlang.h>
#include "MainMenu.h"
#include "Game.h"
#include "GameMenu.h"
#include "Level.h"

/*
Dimensioni della finestra di gioco
*/
#define WIDTH 640        
#define HEIGHT 480

int mainW; // la main viewport

/*
I 3 componenti fondamentali del gioco
*/
MainMenu* mainMenu;	     
Game* tnr;
Level* lv;

int timerForDiff = 1000;      //timer per la velocità dei nemici - Default 1000

/*
 Inizializzazione degli oggetti creati Menu-Livello-Gioco-Caricamento texture
*/
void init()                 
{
	mainMenu = new MainMenu(WIDTH,HEIGHT);
	lv = new Level(1,mainMenu->getDiff());
	tnr = new Game(WIDTH,HEIGHT,lv);
	timerForDiff = lv->getSpeed();
	tnr->initTexture();
}
/*
Disegno del contenuto della finestra
*/
void draw()
{
	
	if(!mainMenu->isNewGame()){            //Disegna il menu principale finchè non inizia la partita
	  mainMenu->reshape(WIDTH,HEIGHT);
	  mainMenu->draw();	
	  
	}

	if(mainMenu->isNewGame())             //Disegna il gioco
	{	
		tnr->draw();
	}
}
/*
Gestisce la tastiera
*/
void keyboard(unsigned char c, int w, int h)
{
	tnr->keyboard(c,w,h);
}
/*
Gestisce il click del mouse
*/
void mouseClick(int button, int state, int x, int y)
{

	if(!mainMenu->isNewGame()){
	 mainMenu->onMouseClick(button,state,x,y);           
	 lv = new Level(1,mainMenu->getDiff());                  //update del livello ad ogni click nel caso della selezione di difficoltà differenti
	 timerForDiff = lv->getSpeed();
	 tnr->setLevel(lv);
	}
	else
		if(tnr->mouseClickFunc(button,state,x,y))           //differenziazione menu principale-secondario nella funzione di click
		{
			mainMenu->newGame = false;
			mainMenu->second = true;
		}
}
/*
Gestisce il movimento del mouse
*/
void mouseMove(int x,int y)
{
	if(!mainMenu->isNewGame())            //Distinzione delle funzioni di gestione del puntatore tra menu principale/secondario
		mainMenu->onMouseMove(x,y);
	else
      tnr->mouseMoveFunc(x,y);	
}
/*
Ridisegna il menu
*/
void reshape(int w,int h){
	mainMenu->reshape(w,h);
}
/*
Funzione idle eseguita periodicamente
*/
void idleFunc()
{
	if(mainMenu->isNewGame())
		tnr->idle();
}
/*
Metodo eseguito ogni timerForDiff: gestisce il movimento dei nemici in base alla difficolta'
*/
void timerFunc(int value)
{
	if(mainMenu->isNewGame()){
		tnr->timerFunction();
	}
	glutTimerFunc(timerForDiff,timerFunc,0);
	glutPostRedisplay();	
}
/*
Il metodo main che setta tutte le primitive OpenGL
*/
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH ,HEIGHT);
	mainW = glutCreateWindow("Take 'n' run");
	init();
	glutDisplayFunc(draw);
	glutIdleFunc(idleFunc);  
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(&mouseClick);
	glutPassiveMotionFunc(&mouseMove);	
	glutTimerFunc(100,timerFunc,0);
	glutMainLoop();
	return(0);
}