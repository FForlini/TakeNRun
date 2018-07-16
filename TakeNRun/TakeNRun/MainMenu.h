#include <string.h> 
#include <iostream>
#include <fstream>                        
#include <glut.h>
#include <Gl/gl.h>

using namespace std;

#pragma once
class MainMenu
{
private:
GLboolean selected1,selected2,selected3,selected4,selected5;          //booleani per la selezione dei bottoni         
GLboolean selected6,selected7,selected9,selected10,selected11;                  
           
GLboolean difficulty,controls,options,how_to_play;           //booleani per difficoltà,nuovo gioco e vari sottomenu            

GLboolean easy,medium,hard;

string version,button1,button2,button3,button4,button6;               //stringhe per il testo dei bottoni
string button7,button9,button10,button11;

ifstream fin;
GLuint title;

int width,height,diff;
int xMouse,yMouse;

public:
	GLboolean second;
	GLboolean newGame;
	MainMenu(int,int);
	virtual ~MainMenu(void);
	GLuint loadTexture(string);
	void draw(void);
	void drawButton(string, float, float, GLboolean );
	void write(string,void*,float ,float );
	void drawTitle(float x,float y);
	void writeLine(char[],int);
	void drawVersion(float,float );
	void setMouseCoordinates(int,int);
	void onMouseMove(int,int);
	void onMouseClick(int,int,int,int);
	void reshape(int,int);
	GLboolean isNewGame();
	void writeFromFile(char[],int);
	void readFromFile();
	int getDiff();
};

