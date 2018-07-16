#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include <iostream>
#include <irrKlang.h>
#include "Level.h"

using namespace std;

#pragma once
class Field
{
private:

Player* p;

int WF,HF;
bool collision;

float randx,randy;

irrklang::ISoundEngine* soundEngine;


public:
	
	Field(int,int);
	~Field(void);
	void random();	
    int geti();
	int getj();
	void checkWallCollision(Player*);
	int checkEnemyCollision(Player*,Enemy**);
	bool checkFoodCollision(Food*,Player*);
	Enemy** getEnemies(Level*);
	void generateEnemies(Level*);
};

