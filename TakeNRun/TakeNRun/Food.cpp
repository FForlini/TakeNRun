#include "Food.h"
#include <Windows.h>
#include "Coordinate.h"
#include <time.h>

using namespace std;

Coordinate* pos; // la posizione del cibo


/*
Costruttore con coordinate specifiche usato per il debug
*/
Food::Food(Coordinate* i)                    
{
	pos = i;
}
/*
Costruttore con posizione casuale per le entità da prendere
*/
Food::Food()                                   
{
	srand(time(NULL));                         
	float x = (rand() % 20 -10) * 10;
	float y = (rand() % 20 -10) * 10;

	pos = new Coordinate(x,y);

}
/*
Distruttore virtuale
*/
Food::~Food(void)
{
}
/*
Ritorna la posione del cibo
*/
Coordinate* Food::getPos()
{
	return pos;
}
