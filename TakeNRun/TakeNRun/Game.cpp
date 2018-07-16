#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <gl\GL.h>
#include <Windows.h>
#include <math.h>
#include <SOIL.h>
#include "Game.h"
#include "Field.h"
#include "Coordinate.h"
#include "Viewport.h"
#include "Player.h"
#include "Food.h"
#include <irrKlang.h>
#include "GameMenu.h"
#include "Level.h"

#define _USE_MATH_DEFINES // per la costante PI GRECO

#define W_FIELD 100 // Le dimensione del campo di gioco in OpenGL Coordinate
#define H_FIELD 100

bool lost,won,isInPause; // booleani che dicono lo stato del gioco rispettivamente: perso, vinto, in pausa

int WIDTH,HEIGHT; // la dimensione dello schermo

int score,tScore; // il punteggio relativo al livello e il punteggio totale

/*
Le variabili che rappresentano le varie texture del gioco
*/
GLuint texTNT;
GLuint texWall[5];
GLuint food;
GLuint foodpos;
GLuint pause;
GLuint lifeT;
GLuint skull;
GLuint texLose,texWin;

/*
Tutti gli oggetti che compongono l'intera struttura del gioco: viewport secondaria, Field, Giocatore, Nemico, Livello, Cibo
*/
Viewport* viewScore;
Field *field;
Player *player1;
Food* f1;
Enemy** en;  
Level* l;

int lives = 4; // il numero di vite inziali

GameMenu* gMenu; // l'oggetto del menu di pause/vittoria/perdita

irrklang::ISoundEngine* irrEngine ; // oggetto per esecuzione di file audio

/*
Il metodo permette il caricamento del file della texture
*/
GLuint Game::getTexture(std::string Filename) 
{
	GLuint tex_ID = 0;

	tex_ID = SOIL_load_OGL_texture(
		Filename.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		| SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_MULTIPLY_ALPHA
		| SOIL_FLAG_COMPRESS_TO_DXT
		| SOIL_FLAG_DDS_LOAD_DIRECT
		| SOIL_FLAG_INVERT_Y
		);

	if( tex_ID > 0 )
	{		
		return tex_ID;
	}
	else
		return 0;
}

/*
Il costruttore dell'oggeto Game: utilizzato per settare le variabili all'inzio del gioco
*/
Game::Game(int w,int h,Level* lv)
{
	WIDTH = w;
	HEIGHT = h;

	l = lv;

	angle = 0;

	lost=false;
	won=false;
	isInPause = false;
	tScore = 0;
	viewScore = new Viewport(WIDTH/2,0,WIDTH/2,HEIGHT/2,lives);
	lives = 4;
	score = 0;
	gMenu = new GameMenu(WIDTH,HEIGHT);

	irrEngine = irrklang::createIrrKlangDevice(); 

	player1 = new Player(new Coordinate(0,0));
	field = new Field(W_FIELD,H_FIELD);
	field->generateEnemies(l);
	en = new Enemy*[lv->getNum()];
	en = field->getEnemies(l);
	f1 = new Food();
	viewScore->setScoreNLevel(tScore,l->getLevel());
}
/*
Inizializza tutti i valori di ogni variabile 
*/
void Game::reset()
{
	angle = 0;

	lost=false;
	won=false;
	isInPause = false;
	lives = 4;
	score = 0;
	viewScore = new Viewport(WIDTH/2,0,WIDTH/2,HEIGHT/2,lives);


	gMenu = new GameMenu(WIDTH,HEIGHT);

	player1 = new Player(new Coordinate(0,0));
	field = new Field(W_FIELD,H_FIELD);
	field->generateEnemies(l);
	en = new Enemy*[l->getNum()];
	en = field->getEnemies(l);
	f1 = new Food();
	viewScore->setScoreNLevel(score,l->getLevel());
}

/*
Distruttore virtuale
*/
Game::~Game(void) 
{

}

/*
Metodo che aggiorna ogni TOT millisecondi la posizione del nemico
*/
void Game::timerFunction()
{
	if(!lost && !won && !isInPause){
		for(int o=0;o<l->getNum();o++)
			en[o]->AI(l->getLevel());
		glutPostRedisplay();
	}

}

/*
Metodo eseguito ciclicamente per il controllo delle collisioni e aggiornamento del punteggio e stato di gioco
*/
void Game::idle()
{
		
	if(!lost && !won  && !isInPause){
		field->checkWallCollision(player1);

		lives = lives - field->checkEnemyCollision(player1,en);

		if(lives <=0)
			lost = true;

		viewScore->setLives(lives);

		if(field->checkFoodCollision(f1,player1))
		{
			f1 = new Food();
			score++;
			tScore++;
			if(score == 10 && l->getLevel() == 1) // primo livello 10 palline
			{
				score = 0;
				won = true;
			}else if(score == 15 && l->getLevel() == 2) // secondo livello 15 palline
			{
				score = 0;
				won = true;
			}else if(score == 20 && l->getLevel() == 3) // terzo livello 20 palline
			{
				score = 0;
				won = true;
			}

			viewScore->setScoreNLevel(tScore,l->getLevel());


		}
		glutPostRedisplay();
	}

}

/*
Metodo per disegnare i muri del gioco con relative texture
*/
void Game::drawWall()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texWall[0]);

	glBegin(GL_QUADS); 

	for(int j=0; j< 200; j+=10)
		for(int i= 0; i < 200; i+= 10)
		{
			glTexCoord2f(0,0);
			glVertex3f( -100, j,-100+i);
			glTexCoord2f(1,0);
			glVertex3f( -100, j,-90+i);
			glTexCoord2f(1,1);
			glVertex3f( -100, 10+j,-90+i);
			glTexCoord2f(0,1);
			glVertex3f( -100, 10+j,-100+i);
		}
		glEnd();



		glBindTexture(GL_TEXTURE_2D, texWall[1]);
		glBegin(GL_QUADS); 

		for(int j=0; j< 200; j+=10)
			for(int i= 0; i < 200; i+= 10)
			{
				glTexCoord2f(0,0);
				glVertex3f( 100, j,-90+i);
				glTexCoord2f(1,0);
				glVertex3f( 100, j,-100+i);
				glTexCoord2f(1,1);
				glVertex3f( 100, 10+j,-100+i);
				glTexCoord2f(0,1);
				glVertex3f( 100, 10+j,-90+i);
			}
			glEnd();


			glBindTexture(GL_TEXTURE_2D, texWall[2]);
			glBegin(GL_QUADS); 

			for(int j=0; j< 200; j+=10)
				for(int i= 0; i < 200; i+= 10)
				{
					glTexCoord2f(0,0);
					glVertex3f( 100-i, j,-100);
					glTexCoord2f(1,0);
					glVertex3f( 90-i, j,-100);
					glTexCoord2f(1,1);
					glVertex3f( 90-i, 10+j,-100);
					glTexCoord2f(0,1);
					glVertex3f( 100-i, 10+j,-100);
				}
				glEnd();

				glBindTexture(GL_TEXTURE_2D, texWall[3]);
				glBegin(GL_QUADS); 

				for(int j=0; j< 200; j+=10)
					for(int i= 0; i < 200; i+= 10)
					{
						glTexCoord2f(0,0);
						glVertex3f( 90-i, j,100);
						glTexCoord2f(1,0);
						glVertex3f( 100-i, j,100);
						glTexCoord2f(1,1);
						glVertex3f( 100-i, 10+j,100);
						glTexCoord2f(0,1);
						glVertex3f( 90-i, 10+j,100);
					}
					glEnd();

					glBindTexture(GL_TEXTURE_2D, texWall[4]);
					glBegin(GL_QUADS); 

					for(int j=0; j< 200; j+=10)
						for(int i= 0; i < 200; i+= 10)
						{
							glTexCoord2f(0,0);
							glVertex3f( -100+i, 0,-100+j);
							glTexCoord2f(1,0);
							glVertex3f( -90+i, 0,-100+j);
							glTexCoord2f(1,1);
							glVertex3f( -90+i, 0,-100+j+10);
							glTexCoord2f(0,1);
							glVertex3f( -100+i, 0,-100+j+10);
						}
						glEnd();

						glDisable(GL_TEXTURE_2D);

}

/*
Caricamento di tutte le texture presenti nel gioco
*/
void Game::initTexture()
{

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	texTNT = getTexture("tnt.png");
	texWall[0] = getTexture("wall1.jpg"); // BEIGE WALL 
	texWall[1] = getTexture("wall2.jpg"); // BLUE WALL
	texWall[2] = getTexture("wall3.jpg"); // RED WALL
	texWall[3] = getTexture("wall4.jpg"); // GREEN WALL
	texWall[4] = getTexture("wall5.jpg"); // GREY WALL

	food = getTexture("food.jpg");
	foodpos = getTexture("food.jpg");

	pause = getTexture("pause.png");
	lifeT = getTexture("life.png");
	skull = getTexture("skull.jpg");

	texLose = getTexture("lose.png");
	texWin = getTexture("win.png");

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//http://www.andersriggelsen.dk/glblendfunc.php
}

/*
Disegno del cubo che rappresenta il nemico con relative texture
*/
void Game::drawCube(GLfloat x,GLfloat y, GLfloat z,GLfloat h,char type) 
{

	glEnable(GL_TEXTURE_2D);
	if(type == 't')
		glBindTexture(GL_TEXTURE_2D, texTNT);
	else
		glBindTexture(GL_TEXTURE_2D, skull);

	glBegin(GL_QUADS);
	// FRONT
	glTexCoord2f(0,0);
	glVertex3f(x,z,y);
	glTexCoord2f(1,0);
	glVertex3f(x+h,z,y);
	glTexCoord2f(1,1);
	glVertex3f(x+h,z+h,y);
	glTexCoord2f(0,1);
	glVertex3f(x,z+h,y);

	// BACK
	glTexCoord2f(0,0);
	glVertex3f(x+h,z,y+h);
	glTexCoord2f(1,0);
	glVertex3f(x,z,y+h);
	glTexCoord2f(1,1);
	glVertex3f(x,z+h,y+h);
	glTexCoord2f(0,1);
	glVertex3f(x+h,z+h,y+h);

	// LEFT
	glTexCoord2f(0,0);
	glVertex3f(x,z,y+h);
	glTexCoord2f(1,0);
	glVertex3f(x,z,y);
	glTexCoord2f(1,1);
	glVertex3f(x,z+h,y);
	glTexCoord2f(0,1);
	glVertex3f(x,z+h,y+h);

	// RIGHT
	glTexCoord2f(0,0);
	glVertex3f(x+h,z,y);
	glTexCoord2f(1,0);
	glVertex3f(x+h,z,y+h);
	glTexCoord2f(1,1);
	glVertex3f(x+h,z+h,y+h);
	glTexCoord2f(0,1);
	glVertex3f(x+h,z+h,y);

	// TOP
	glTexCoord2f(0,0);
	glVertex3f(x,z+h,y);
	glTexCoord2f(1,0);
	glVertex3f(x+h,z+h,y);
	glTexCoord2f(1,1);
	glVertex3f(x+h,z+h,y+h);
	glTexCoord2f(0,1);
	glVertex3f(x,z+h,y+h);

	//BOTTOM
	glTexCoord2f(0,0);
	glVertex3f(x+h,z,y);
	glTexCoord2f(1,0);
	glVertex3f(x,z,y);
	glTexCoord2f(1,1);
	glVertex3f(x,z,y+h);
	glTexCoord2f(0,1);
	glVertex3f(x+h,z,y+h);

	glEnd();


	glDisable(GL_TEXTURE_2D);
}

/*
Disegno del quadrato che sta alla base della pallina che il giocatore deve mangiare
*/
void Game::drawFoodPos(GLfloat x,GLfloat y,GLfloat z)
{
	GLfloat h = 10;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, foodpos);

	glBegin(GL_QUADS);

	glTexCoord2f(0,0);
	glVertex3f(x,z,y);
	glTexCoord2f(1,0);
	glVertex3f(x+h,z,y);
	glTexCoord2f(1,1);
	glVertex3f(x+h,z,y+h);
	glTexCoord2f(0,1);
	glVertex3f(x,z,y+h);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/*
Disegno del rettangolo che rappresenta il giocatore e il nemico nella viewport in 2D
*/
void Game::drawRect(Coordinate* c1)
{
	glBegin(GL_QUADS);
	glVertex2f(c1->getX(),c1->getY());
	glVertex2f(c1->getX(),c1->getY()+10);
	glVertex2f(c1->getX()+10,c1->getY()+10);
	glVertex2f(c1->getX()+10,c1->getY());
	glEnd();
}

/*
Disegno del campo di gioco in 2D
*/
void Game::draw2DField()
{
	glColor3f( 0.8, 0.8, 0.8 ); 
	glBegin(GL_LINES);
	for(int i= 0; i <= 200; i+= 10)
	{
		glVertex2f( -100+i,  100);
		glVertex2f( -100+i, -100);
		glVertex2f( -100,   -100+i);
		glVertex2f( 100,  -100+i);
	}
	glEnd( );
}

/*
Disegno della pallina che rappresenta l'obiettivo del giocatore
*/
void Game::drawFood(GLfloat x,GLfloat y)
{
	drawFoodPos(x,y,0);

	GLUquadric *qobj = gluNewQuadric();

	gluQuadricTexture(qobj,GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,food);

	glPushMatrix();


	glTranslatef(x+5,5,y+5);
	gluSphere(qobj,2,50,50);

	glPopMatrix();

	gluDeleteQuadric(qobj);
	glDisable(GL_TEXTURE_2D); 

}

/*
Il metodo principale della classe. Disegna tutti componenti del gioco: nemici, muri, campo di gioco, texture etc...
*/
void Game::draw()
{

	if(!lost && !won && !isInPause) // nel caso non ci si trova nello stato LOST o WON o INPAUSE allora disegna l'area di gioco
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// VIEWPORT IN ALTO A DESTRA
		glViewport( WIDTH*2/3, HEIGHT/2, WIDTH/3, HEIGHT/2 );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
		gluOrtho2D(-130*((HEIGHT/2)/(WIDTH/3)),130*((HEIGHT/2)/(WIDTH/3)),-130*((HEIGHT/2)/(WIDTH/3)),130*((HEIGHT/2)/(WIDTH/3)));
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		draw2DField();

		glPushMatrix( );
		glColor3f( 0, 0, 1 );
		drawRect(new Coordinate(player1->getX2D(),player1->getY2D()));
		glPopMatrix( );

		glPushMatrix( );

		for(int t=0;t<l->getNum();t++)
		{
			if(en[t]->getType() == 't')
				glColor3f( 1, 0, 0 );
			else
				glColor3f(1,1,1);

			drawRect(new Coordinate(en[t]->getCoord()->getY(),en[t]->getCoord()->getX()));

		}
		glPopMatrix( );

		glPushMatrix();
		glColor3f(1.0,0.7,0.1);
		drawRect(new Coordinate(f1->getPos()->getY(),f1->getPos()->getX()));
		glPopMatrix();

		viewScore->drawVS(lifeT);  // viewport del punteggio e livello                

		// VIEWPORT CENTRALE
		glViewport(0, 0, WIDTH*2/3, HEIGHT);
		glEnable(GL_DEPTH_TEST);
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 45, 1.137, 0.1, 600 );
		glMatrixMode( GL_MODELVIEW );

		glLoadIdentity();

		gluLookAt(player1->getXCam(), player1->getYCam(), player1->getZCam(), player1->getXCam()+player1->getDirX(), player1->getYCam()+player1->getDirY(), player1->getZCam()+player1->getDirZ(), 0, 1, 0);
		drawFood(f1->getPos()->getX(),f1->getPos()->getY());
		drawWall();

		glPushMatrix( );
		for(int i=0;i<l->getNum();i++)
			drawCube(en[i]->getCoord()->getX(),en[i]->getCoord()->getY(),0,10,en[i]->getType());
		glPopMatrix( );	

	}
	else if(lost) // stato LOST: disegno del menu relativo
	{
		glutSwapBuffers();
		gMenu->draw(texLose,false,tScore);

	}else if(won) // stato WON: disegno del menu relativo
	{
		glutSwapBuffers();
		gMenu->draw(texWin,true,tScore);
	}else 
		if(isInPause) // stato INPAUSE: disegno del menu relativo
		{
			glutSwapBuffers();
			gMenu->draw(pause,true,tScore);
		}

		glutSwapBuffers( );
}
/*
Gestisce il movimento del mouse
*/
void Game::mouseMoveFunc(int xMouse,int yMouse)
{
	if(lost || won || isInPause)
	{
		gMenu->onMouseMove(xMouse,yMouse);
	}



}

/*
Gestisce le azioni al click del mouse
*/
bool Game::mouseClickFunc(int button,int state,int xMouse,int yMouse)
{

	if(lost || won || isInPause)
	{

		if(gMenu->onMouseClick(button,state,xMouse,yMouse))
		{

			if(isInPause)
				isInPause = false;
			else
				if(won)
				{
					l = new Level(l->getLevel() + 1,l->getDiff());
					reset();
					won = false;

					if(l->getLevel() == 4)
						return true;
					else
						viewScore->setScoreNLevel(tScore,l->getLevel());

				}else if(lost){
					reset();
					return true;
				}

		}

	}

	return false;
}

/*
Setta il livello di gioco e aggiorna gli oggetti di gioco relativi
*/
void Game::setLevel(Level* le){
	l = le;
	field->generateEnemies(l);
	en = new Enemy*[l->getNum()];
	en = field->getEnemies(l);
}

/*
Gestione della tastiera
*/
void Game::keyboard(unsigned char c, int w, int h)
{
	if(!lost && !won && !isInPause){

		switch(c) {

		case 'w':  
			player1->goStraight(10.f);
			player1->up(10.f);
			break;

		case 'a': 
			player1->turnLeft();
			player1->left();
			break;
		case 's':		
			player1->goBack(10.f);
			player1->down(10.f);
			break;
		case 'd':
			player1->turnRight();
			player1->right();
			break;
		case 'p': if(!isInPause)
					  isInPause = true;
				  else
					  isInPause = false;
			break;

		}
	}

}
