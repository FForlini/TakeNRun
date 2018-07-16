#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include "Level.h"
#include <Windows.h>
#include <iostream>
#include <time.h>         
#include <irrKlang.h>

using namespace std; 

Player* p; // il giocatore

int WF,HF; // le dimensioni del campo di gioco

/*
 Vettori per gli oggetti "nemico" a seconda del livello
*/
Enemy** en1 = new Enemy*[6];                  
Enemy** en2 = new Enemy*[10];
Enemy** en3 = new Enemy*[11];

irrklang::ISoundEngine* soundEngine; // oggetto per il caricamento dell'audio

/*
Il costruttore che setta le variabile ai valori iniziali
*/
Field::Field(int w,int h)
{
	WF = w;
	HF = h;
	collision=false;
	soundEngine = irrklang::createIrrKlangDevice();
}

/*
Distruttore virtuale
*/
Field::~Field(void)
{
}

/*
 Metodo per controllare le collisioni tra giocatore e spazio di gioco (muri)
*/
void Field::checkWallCollision(Player* player)            
{
	p = player;

	if(player->getZCam() < -90)                                
		player->setZCam(-95);
	if(player->getZCam() > 90)
		player->setZCam(95);
	if(player->getXCam() > 90)
		player->setXCam(95);
	if(player->getXCam() < -90)
		player->setXCam(-95);

	if(player->getX2D()<-100)
		player->setX2D(-100);
	if(player->getY2D()>90)
		player->setY2D(90);
	if(player->getY2D()<-100)
		player->setY2D(-100);
	if(player->getX2D()>90)
		player->setX2D(90);	
}


/*
Genera i nemici in base al livello 
*/
void Field::generateEnemies(Level* l)
{
	switch(l->getLevel())
	{
	case 1:   srand(time(NULL));

		for(int k=0;k<l->getNTnt();k++)
			en1[k] = new Enemy('t');

		for(int r = l->getNTnt();r<l->getNTnt()+l->getNSkull();r++)
			en1[r] = new Enemy('s');
		break;

	case 2: srand(time(NULL));
		for(int k=0;k<l->getNTnt();k++)
			en2[k] = new Enemy('t');
		for(int r = l->getNTnt();r<l->getNTnt()+l->getNSkull();r++)
			en2[r] = new Enemy('s');
		break;

	case 3: srand(time(NULL));
		for(int k=0;k<l->getNTnt();k++)
			en3[k] = new Enemy('t');
		for(int r = l->getNTnt();r<l->getNTnt()+l->getNSkull();r++)
			en3[r] = new Enemy('s');
		break;
	}
}

/*
Ritorna i vettori dei nemici in base al livello
*/
Enemy** Field::getEnemies(Level* l)
{
	switch(l->getLevel())
	{
	case 1:  return en1;
		break;
	case 2: return en2;
		break;

	case 3: return en3;
		break;
	}
}
/*
Controlla la collisione tra nemici e player
*/
int Field::checkEnemyCollision(Player* p,Enemy** tnt1)
{
	for(int i=0;i<6;i++)
		if(p->getX2D() == tnt1[i]->getCoord()->getY() && p->getY2D() == tnt1[i]->getCoord()->getX())
		{

			if(tnt1[i]->getType() == 't')
			{
				tnt1[i] = new Enemy('t');
				soundEngine->play2D("tnt.wav",false);
				return 1;
			}
			else if(tnt1[i]->getType() == 's')
			{
				tnt1[i] = new Enemy('s');
				soundEngine->play2D("laugh.mp3",false);
				return 2;
			}
		}		

		return 0;
}
/*
Controlla la collisione tra player e cibo
*/
bool Field::checkFoodCollision(Food* f,Player* p)
{
	if(f->getPos()->getX() == p->getY2D() && f->getPos()->getY() == p->getX2D())
	{

		soundEngine->play2D("blop.wav",false);
		return true;
	}

	return false;
}

