#include "Coordinate.h"   //L'intera classe serve per gestire la posizione degli oggetti all'interno del piano di gioco e della mini-mappa 2D

float x,y; // Le coordinate x e y

Coordinate::Coordinate()
{
}

/*
Il costruttore che setta le coordinate
*/
Coordinate::Coordinate(float x,float y)
{
	this->x = x;
	this->y = y;
}

Coordinate::~Coordinate(void)
{
}

/*
Ritorna la coordinata x
*/
float Coordinate::getX(){
	return this->x;
}

/*
Ritorna la coordinate y
*/
float Coordinate::getY(){
	return this->y;
}
	
/*
Setta il valore della coordinate x
*/
void Coordinate::setX(float x)
{
	this->x = x;
}
/*
Setta il valore della coordinate y
*/
void Coordinate::setY(float y){
	this->y = y;
}
