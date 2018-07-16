#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Player.h"
#include "Coordinate.h"

using namespace std;

/*
Variabili per gestire la telecamera del giocatore
*/
float cameraX,cameraY,cameraZ;          
float dirX,dirY,dirZ;
float angle;
float x2d,y2d;
int pos_current;

Coordinate* playerPos; // posizione del giocatore

/*
Costruttore per settare le variabili
*/
Player::Player(Coordinate* ps)
{
	playerPos = ps;
	cameraX = ps->getX()-5;
	cameraY = 10;
	cameraZ = ps->getY()+5;
	dirY = 0;
	x2d = 0;
	y2d = -10;
	pos_current = 0;
	angle = M_PI/2;
	dirX = sin(angle);
	dirZ = -cos(angle);
}
/*
Distruttore virtuale
*/
Player::~Player(void)
{
}


/*
Metodi per settare e ritornare le variabili per la gestione del player 3D
*/
float Player::getDirX()
{
	return dirX;
}

float Player::getDirY()
{
	return dirY;
}

float Player::getDirZ()
{
	return dirZ;
}

float Player::getXCam()
{
	return cameraX;
}

float Player::getYCam()
{
	return cameraY;
}

float Player::getZCam()
{
	return cameraZ;
}

void Player::setZCam(float cz)
{
	cameraZ = cz;
}

void Player::setXCam(float cx)
{
	cameraX = cx;
}

void Player::setYCam(float cy)
{
	cameraY = cy;
}

/*
Metodo per aggiornare la telecamera quando si avanza
*/
void Player::goStraight(float speed)     
{
	cameraX += dirX * speed;
	cameraY += dirY * speed;
	cameraZ += dirZ * speed;
}
/*
Metodo per aggiornare la telecamera quando si indietreggia
*/
void Player::goBack(float speed)         
{
	cameraX -= dirX * speed;
	cameraY -= dirY * speed;
	cameraZ -= dirZ * speed;
}
/*
Metodo per aggiornare la direzione 
*/
void Player::turnLeft()
{
    angle -= M_PI / 2;
	dirX = sin(angle);
	dirZ = -cos(angle); 
}
/*
Metodo per aggiornare la direzione 
*/
void Player::turnRight()
{
	angle += M_PI / 2;
	dirX = sin(angle);
	dirZ = -cos(angle);
}

/*
Gestione della direzione a seconda dei possibili stati del giocatore nella viewport 2D (girato verso dx,verso sx, etc.)
*/
void Player::up(float speed)
{
	if(pos_current == 0 || pos_current == 4 || pos_current == -4)            
	{
			y2d += speed;
			pos_current = 0;
	}
	if(pos_current == 1)
			x2d += speed;		
	if(pos_current == 2 || pos_current == -2)
			y2d -= speed;		
	if(pos_current == 3 || pos_current == -1)
			x2d -= speed;
	if(pos_current == -3)
		x2d += speed;
	
	playerPos = new Coordinate(x2d,y2d);                // Aggiorna la posizione in Coordinate del giocatore
}
/*
Gestione della direzione a seconda dei possibili stati del giocatore nella viewport 2D (girato verso dx,verso sx, etc.)
*/
void Player::down(float speed)
{
	if(pos_current == 0 || pos_current == -4 || pos_current == 4){
			y2d -= speed;
			pos_current = 0;
		}
		if(pos_current == -1){
			x2d += speed;	
		}
		if(pos_current == -2 || pos_current == 2){
			y2d += speed;		
		}
		if(pos_current == -3 || pos_current == 1){
			x2d -= speed;	
		}
		if(pos_current == 3)
		  x2d -= speed;

		playerPos = new Coordinate(x2d,y2d); // Aggiorna la posizione in Coordinate del giocatore
}
/*
Gestione della direzione a seconda dei possibili stati del giocatore nella viewport 2D (girato verso dx,verso sx, etc.)
*/
void Player::right()
{
	if(pos_current != 4)
	  pos_current++;	
	else
		pos_current = 1;

}
/*
Gestione della direzione a seconda dei possibili stati del giocatore nella viewport 2D (girato verso dx,verso sx, etc.)
*/
void Player::left()
{
	if(pos_current != -4)
	  pos_current--;	
	else
		pos_current = -1;
	
}
/*

Metodi per settaggio e ritorno variabile player 2D

*/


float Player::getX2D()
{
	return x2d;
}

float Player::getY2D()
{
	return y2d;
}

void Player::setX2D(float x)
{
	x2d = x;
}

void Player::setY2D(float y)
{
	y2d = y;
}