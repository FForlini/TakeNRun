#include "Enemy.h"
#include <time.h>
#include <iostream>
#include <Windows.h>

using namespace std;

/*
Variabili per l'algoritmo di movimento del nemico
*/
int contX,contY;
bool dctx,dcty,ud;

char type;// il tipo di nemico

Coordinate* posEnemy; // la posizione del nemico

/*
Costruttore per il nemico in base alle coordinate date
*/
Enemy::Enemy(Coordinate* e,char t)              
{
	posEnemy = e;
	contX = 0;
	contY = 0;
	dctx = false;
	dcty = false;
	type = t;
	ud = false;
}
/*
Costruttore per il nemico in posizione random (differenziato sulla base del tipo di nemico)
*/
Enemy::Enemy(char t)                           
{

	float x = (rand() % 20 -10) * 10;
	float y = (rand() % 20 -10) * 10;
	contX = 0;
	contY = 0;
	posEnemy = new Coordinate(x,y);
	dctx = false;
	dcty = false;
	type = t;
	ud = false;
}
/*
Distruttore virtuale
*/
Enemy::~Enemy(void)
{
}

/*
Metodo per l'update della posizione del nemico generico in base alle coordinate passate
*/
void Enemy::updatePosition(int x,int y)           
{
	int tempX = posEnemy->getX(),tempY = posEnemy->getY();
	posEnemy->setX(tempX + x);
	posEnemy->setY(tempY + y);
}
/*
Metodo per la generazione del corretto numero di nemici per ciascun livello
*/
void Enemy::AI(int level)                                
{
	int x = posEnemy->getX(), y = posEnemy->getY();

	switch(level)
	{
	case 1: level1_2(x,y,6);
		break;

	case 2: level1_2(x,y,8);
		break;
	case 3: level3(x,y,6);

		break;
	}
}
/*
Ritorna la posizione del nemico in Coordinate
*/
Coordinate* Enemy::getCoord()
{
	return posEnemy;
}
/*
Ritorna il tipo di nemico
*/
char Enemy::getType()
{
	return type;
}
/*
Metodo per l'update della posizione in base al percorso predefinito seguito dai nemici
*/
void Enemy::level3(int x,int y,int len)  // Metodo simile a level1_2                          
{
	if(x - contX*10 + len*10 < 100 && !ud) 
	{
		if(contX >= 0 && contX < len && !dctx)
		{
			updatePosition(10,0);
			contX++;
		}
		else{ 
			dctx = true;
			if(y + 10 < 100 && !dcty) 
			{
				if(contY != 1)
					updatePosition(0,10);
				else
					updatePosition(0,-10);
				if(y - 10 < -100)
					contY = 0;
				dcty = true;
			}			  
			else
			{
				if(contX >= len && contX < 2*len)
				{
					updatePosition(-10,0);
					contX++;
				}
				else{
					if(y + 10 >= 100){
						updatePosition(0,-10);
						dctx = false;
						contY = 1;
					}
					else{

						contX = 0;
						dcty = false;
						dctx = false;
					}
				}
			}
		}

	}
	else if(x - contX*10 - len*10 > -100 )
	{
		ud = true;
		if(contX >= 0 && contX < len && !dctx)
		{
			updatePosition(-10,0);
			contX++;
		}
		else {

			dctx = true;
			if(y + 10 < 100 && !dcty)
			{
				if(contY != 1)
					updatePosition(0,10);
				else
					updatePosition(0,-10);
				if(y - 10 < -100)
					contY = 0;
				dcty = true;
			}			  
			else
			{
				if(contX >= len && contX < 2*len)
				{
					updatePosition(10,0);
					contX++;
				}
				else{
					if(y + 10 >= 100){
						updatePosition(0,-10);
						dctx = false;
						contY = 1;
					}
					else{

						contX = 0;
						dcty = false;
						dctx = false;
					}
				}
			}
		}


	}
	else
		ud = false;

}
/*
Metodo per l'update della posizione in base al percorso predefinito seguito dai nemici
*/
void Enemy::level1_2(int x,int y ,int len)              
{
	if(x - contX*10 + len*10 < 100 && !dctx) // Se il nemico non esce dal campo 20x20...
	{
		if(contX >= 0 && contX < len) // ...effettua il movimento di len posizioni verso l'alto (RICORDARE: gli assi della visualizzazione in 2D sono invertiti rispetto al classico concetto di assi cartesiani)
		{
			updatePosition(10,0);
			contX++;
		}
		else
			if(y - contY*10 + len*10 < 100 && !dcty) // controlla se il nemico non sta uscendo dal campo 20x20
			{

				if(contY >=0 && contY < len) // Effettua il movimento di len posizioni
				{
					updatePosition(0,10);
					contY++;
				}
				else if(contX >= len && contX < 2*len) // torna indietro per completare il movimento RICORDARE: il movimento è a forma di quadrato
				{
					updatePosition(-10,0);
					contX++;
				}
				else if(contY >= len && contY < 2*len)// ...completamenteo del movimento
				{
					updatePosition(0,-10);
					contY++;
				}
				else // appena ha finito setta a 0 i contatori delle posizioni per poter ricominciare da capo
				{
					contX = 0;
					contY = 0;
				}


			}
			else // stesso procedimento nel caso in cui il movimento precendente porta il nemico ad uscire dal campo 20x20 ASSE Y
			{
				dcty = true;
				if(contY >=0 && contY < len)
				{
					updatePosition(0,-10);
					contY++;
				}
				else if(contX >= len && contX < 2*len)
				{
					updatePosition(-10,0);
					contX++;
				}
				else if(contY >= len && contY < 2*len)
				{
					updatePosition(0,10);
					contY++;
				}
				else 
				{
					contX = 0;
					contY = 0;
					dcty = false;
				}


			}
	}else { // stesso procedimento con movimento simmetrico a causa dell'uscita del campo del nemico ASSE X

		dctx = true;
		if(contX >= 0 && contX < len)
		{
			updatePosition(-10,0);
			contX++;
		}
		else
			if(y - contY*10 + len*10 < 100 && !dcty)
			{

				if(contY >=0 && contY < len)
				{
					updatePosition(0,10);
					contY++;
				}
				else if(contX >= len && contX < 2*len)
				{
					updatePosition(10,0);
					contX++;
				}
				else if(contY >= len && contY < 2*len)
				{
					updatePosition(0,-10);
					contY++;
				}
				else 
				{
					contX = 0;
					contY = 0;
				}

			}
			else
			{
				dcty = true;
				if(contY >=0 && contY < len)
				{
					updatePosition(0,-10);
					contY++;
				}
				else if(contX >= len && contX < 2*len)
				{
					updatePosition(10,0);
					contX++;
				}
				else if(contY >= len && contY < 2*len)
				{
					updatePosition(0,10);
					contY++;
				}
				else 
				{
					contX = 0;
					contY = 0;
					dcty = false;
					dctx = false;
				}


			}
	}


}