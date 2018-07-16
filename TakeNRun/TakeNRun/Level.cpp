#include "Level.h"

/*
Variabili di ciascun livello: velocità nemici, numero tnt, numero skull, livello, difficoltà selezionata
*/
int speed;                          
int nTnt,nSkull;
int level,dff;

/*
Costruttore per setttare tutte le variabile al proprio valore iniziale
*/
Level::Level(int lv,int diff)
{
	level = lv;
	dff = diff;

	//inizializzazioni delle variabili a seconda della difficoltà selezionata e del livello corrente

	switch (lv)
	{
	case 1: switch(diff)                                          
			{
				case 0: speed = 1000; nTnt = 6; nSkull = 0; break;
				case 1: speed = 600;  nTnt = 5; nSkull = 1; break;
				case 2: speed = 200;  nTnt = 4; nSkull = 2; break;
			} break;

	case 2: switch(diff)
			{
				case 0: speed = 1000;nTnt = 9; nSkull = 1; break;
				case 1: speed = 600; nTnt = 7; nSkull = 3; break;
				case 2: speed = 200; nTnt = 5; nSkull = 5; break;
			}
		break;


	case 3: switch(diff)
			{
				case 0: speed = 1000;nTnt = 6; nSkull = 5; break;
				case 1: speed = 600; nTnt = 5; nSkull = 6; break;
				case 2: speed = 200; nTnt = 4; nSkull = 7; break;
			}
		break;
	
	default:
		break;
	}
}

/*
Metodo per tornare il numero di nemici presenti in ciascun livello
*/
int Level::getNum()   
{
	switch(level)
	{
	 case 1:  return 6;
			  break;
	 case 2: return 10;
		     break;

	 case 3: return 11;
		 break;
	}
}
/*
Distruttore virtuale
*/
Level::~Level(void)
{
}
/*
Ritorna la velocità del nemico
*/
int Level::getSpeed()
{
	return speed;
}
/*
Ritorna il numero dei TNT
*/
int Level::getNTnt()
{
	return nTnt;
}
/*
Ritorn il numero degli Skull
*/
int Level::getNSkull()
{
	return nSkull;
}
/*
Ritorna il livello
*/
int Level::getLevel()
{
	return level;
}
/*
Ritorna la difficolta'
*/
int Level::getDiff()
{
 return dff;
}
