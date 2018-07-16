#include <iostream>
#include <fstream>
#include <string.h>                            
#include <glut.h>
#include <Gl/gl.h>
#include <SOIL.h>
#include <irrKlang.h>
#include "MainMenu.h"

using namespace std;  

irrklang::ISoundEngine* engine ;

GLboolean selected1,selected2,selected3,selected4,selected5;          //booleani per la selezione dei bottoni         
GLboolean selected6,selected7,selected9,selected10,selected11;                  
           
GLboolean newGame, difficulty,second,controls,options,how_to_play;           //booleani per difficoltà,nuovo gioco e vari sottomenu            

GLboolean easy,medium,hard;

string version,button1,button2,button3,button4,button6;               //stringhe per il testo dei bottoni
string button7,button9,button10,button11;

ifstream fin;
GLuint title;

int width,height,diff;
int xMouse,yMouse;

/*
Costruttore per settare tutte le variabili a rispettivi valori inziali
*/
MainMenu::MainMenu(int w,int h)
{
	width = w;
	height = h;
	selected1 = false;                   
	selected2 = false;                   
	selected3 = false;                   
	selected4 = false;	
	selected6 = false;                   
	selected7 = false;  
	selected9 = false;                   
	selected10 = false;                   
	selected11 = false;                   
	newGame = false;
	options = false;
	controls=false;
	how_to_play = false;
	second=false;
	difficulty=false;
	easy=false;
	medium=false;
	hard=false;

	version= "v. 1.0.0";
	button1= "Nuovo gioco";
	button2= "Difficolta'";
	button3= "Opzioni";
	button4= " < Indietro";	
	button6= "Controlli";
	button7= "Come giocare";
	button9= "Facile";
	button10= "Medio";
	button11= "Difficile";

	engine = irrklang::createIrrKlangDevice();    
	diff = 0;	
}
/*
Distruttore virtuale
*/
MainMenu::~MainMenu(void)
{
}

/*
Metodo per il caricamento delle texture
*/
GLuint MainMenu::loadTexture(std::string Filename){                

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
Disegno del testo generico
*/
void MainMenu::write(string s,void *font ,float x,float y){

	glRasterPos2f(x-2,y);

	for(int i=0; i<s.length(); i++){               //disegna il testo
		if(s[i]=='\n')
			glutBitmapCharacter(font, NULL);          //EOF
		else
		glutBitmapCharacter(font, (int) s[i]);
	}
}
/*
Metodo che scrive il contenuto del file
*/
void MainMenu::writeFromFile(char array[],int end)          //Metodo per scrivere da file .txt
{
	char *buf; 
	int aux=0;                                     //puntatore ausiliario
	float n=3;                                     //altezza dell'inizio del testo
	buf=new char[end];                             //dinamically allocate memory	
	for(int j=0;j<end;j++,aux++){

		buf[aux]=array[j];

		if(array[j]=='\n'){
		write(buf,GLUT_BITMAP_9_BY_15,-5,n);       

		buf=new char[end];                         //svuotamento del buffer
		aux=0;                                     //reset a 0 del puntatore ausiliario
		n=n-0.7;
		}
	}
	delete buf;                                    //cancellazione del buffer
}
/*
Metodo che legge da file
*/
void MainMenu::readFromFile(){
	int end,i=0;
			char *array;                                     //allocazione dinamica della memoria
			if(how_to_play)
			fin.open("How_to_play.txt");                     //apertura del file
			else
				fin.open("Controls.txt");   
			fin.seekg (0, ios::end);
			end = fin.tellg();                               //posizionamento alla dine del file x il calcolo della dimensione del buffer
			fin.seekg(0,ios::beg);

			array=new char[end];                             //creazione array di dimensione buffer	
			glColor3f(0,1,0);
			while(!fin.eof()){                               //lettura del file
				fin.get(array[i]);
				i++;				
			}                                         //METODO????
			
			writeFromFile(array,end);			
			delete array;                                    //rilascio memoria allocata
			fin.close();                                      //chiusura del file
			
			glPopMatrix();
}
/*
Disegno del bottone
*/
void MainMenu::drawButton(string s,float x,float y,GLboolean selected){
	if(!second){                                 

	glColor3f(1.0,0.3,0.1);                      //colore arancione 

	if(selected)
	glPolygonMode(GL_FRONT, GL_FILL);            
	else
	glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_QUADS);                          //disegna il bottone
	glVertex2f(x,y);
	glVertex2f(x+6,y);
	glVertex2f(x+6,y+2);
	glVertex2f(x,y+2);
	glEnd();

	if(selected)
	glColor3f(0,0,0);                           //cambia il colore del testo per renderlo visibile quando selezionato

	write(s,GLUT_BITMAP_9_BY_15,x+3,y+1);
	}
	else
	{
		if(selected)
	glColor3f(0,0,0);                           

	write(s,GLUT_BITMAP_9_BY_15,x+3,y+1);
	glColor3f(1.0,0.3,0.1);

	if(selected)
	glPolygonMode(GL_FRONT, GL_FILL);        
	else
	glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_QUADS);                         
	glVertex2f(x,y);
	glVertex2f(x+6,y);
	glVertex2f(x+6,y+2);
	glVertex2f(x,y+2);
	glEnd();
	}
}
/*
Metodo per l'assgnazione di texture del titolo
*/
void MainMenu::drawTitle(float x,float y){                         

	glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    title = loadTexture("title.png");                   
	glBindTexture(GL_TEXTURE_2D,title);                            //binding della texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
    glBegin(GL_QUADS);
	// FRONT
	glTexCoord2f(0,0);
	glVertex2f(x+10,y);
	glTexCoord2f(1,0);
	glVertex2f(x,y);
	glTexCoord2f(1,1);
	glVertex2f(x,y+2);
	glTexCoord2f(0,1);
	glVertex2f(x+10,y+2);
		
	glEnd();
	glDisable(GL_TEXTURE_2D);
			
}
/*
Metodo per disegnare la versione di gioco
*/
void MainMenu::drawVersion(float x,float y){          
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0,1,0);                     
	write(version,GLUT_BITMAP_9_BY_15,x+2,y+0.1); 
	write("COPY BY FORLINI:CARRARA 2013",GLUT_BITMAP_9_BY_15,x+0.3,y+0.1);
	glPopMatrix();

	glColor3f(1.0,0.3,0.1);
}
/*
Disegna l'intero menu
*/
void MainMenu::draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               //Pulisce i buffer ogni volta che viene richiamato draw(),per evitare difetti

	drawButton(button1,-3.5,1,selected1);
	drawButton(button2,-3.5,-2,selected2);
	drawButton(button3,-3.5,-5,selected3);

	drawTitle(-5.5,4);
	drawVersion(0.75,-1);

	if(difficulty){                                                  //sottomenu difficoltà

		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawButton(button4,-7,4,selected4);
		drawButton(button9,-1,1,selected9);
	    drawButton(button10,-1,-2,selected10);
	    drawButton(button11,-1,-5,selected11);

	}

	if(options){                                                   //sottomenu opzioni

		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		drawButton(button4,-7,4,selected4);
		drawButton(button6,0,0,selected6);
		drawButton(button7,0,-4,selected7);
		
		if(how_to_play){                                          //sottomenu how-to play

			glPushMatrix();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			drawButton(button4,-7,4,selected4);			
		readFromFile();
		glPopMatrix();
		}

		if(controls){                                    //sottomenu controlli

			glPushMatrix();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			drawButton(button4,-7,4,selected4);				
			readFromFile();
			glPopMatrix();
		}

		glPopMatrix();
	}
		
	glutSwapBuffers();
}
/*
Gestisce il movimento del mouse
*/
void MainMenu::onMouseMove(int xMouse,int yMouse){
	
	float k = 1.0;                                                           //fattore di scala per diverse risoluzioni

	if(width==800)
		k=1.25;                                                              //correzione scala												

	if(xMouse<398*k && xMouse>207*k && yMouse<207*k && yMouse>144*k)         //NEW GAME
		selected1=true;
	else
		selected1=false;

	if(xMouse<398*k && xMouse>207*k && yMouse<302*k && yMouse>241*k)          //DIFFICULTY
		selected2=true;
	else
		selected2=false;

	if( difficulty &&  xMouse<479*k && xMouse>289*k && yMouse<207*k && yMouse>144*k || easy)    //EASY
		selected9=true;
	else
		selected9=false;

	if( difficulty && xMouse<479*k && xMouse>289*k && yMouse<304*k && yMouse>241*k || medium)   //MEDIUM
		selected10=true;
	else
		selected10=false;

	if( difficulty && xMouse<479*k && xMouse>289*k && yMouse<399*k && yMouse>336*k || hard)    //HARD
		selected11=true;
	else
		selected11=false;

	if(xMouse<398*k && xMouse>207*k && yMouse<398*k && yMouse>337*k)          //OPTIONS
		selected3=true;
	else
		selected3=false;

	if((options || difficulty) && xMouse<287*k && xMouse>96*k && yMouse<112*k && yMouse>49*k)          //BACK
		selected4=true;
	else
		selected4=false;

	if(options && xMouse<511*k && xMouse>319*k && yMouse<239*k && yMouse>176*k)          //CONTROLS
		selected6=true;
	else
		selected6=false;

	if(options && xMouse<511*k && xMouse>319*k && yMouse<366*k && yMouse>305*k)          //HOW TO PLAY
		selected7=true;
	else
		selected7=false;
		    
	glutPostRedisplay();
}
/*
Gestisce il click del mouse
*/
void MainMenu::onMouseClick(int button,int state,int xMouse,int yMouse)
{
	float k = 1.0;                               //fattore di scala

	if(width==800)
	 k=1.25;                                       

	if(!options && !difficulty && xMouse<382*k && state==GLUT_DOWN && xMouse>191*k && yMouse<398*k && yMouse>337*k){                     //click su OPTIONS
		options=true;
	    engine->play2D("Tick.mp3",false);
	}
		
	if(!difficulty && xMouse<382*k && xMouse>191*k && yMouse<302*k && yMouse>241*k && state==GLUT_UP){                     //click su DIFFICULTY
		difficulty=true;
	    engine->play2D("Tick.mp3",false);
	}

	if(!options && !difficulty && xMouse<382*k && xMouse>191*k && yMouse<208*k && yMouse>144*k && state==GLUT_DOWN){                     //clisck su NEW GAME
		engine->play2D("Tick.mp3",false);
		newGame=true;
	}

	if(difficulty && state==GLUT_DOWN && xMouse<479*k && xMouse>289*k && yMouse<207*k && yMouse>144*k){          //settaggio delle difficoltà e,m,h
		diff = 0;
		easy=true;
		medium=false;
		hard=false;
		engine->play2D("Tick.mp3",false);
	}

	if( difficulty && state==GLUT_DOWN && xMouse<479*k && xMouse>289*k && yMouse<304*k && yMouse>241*k){
		diff = 1;
		easy=false;
		medium=true;
		hard= false;
		engine->play2D("Tick.mp3",false);
	}
	if( difficulty && state==GLUT_DOWN && xMouse<479*k && xMouse>289*k && yMouse<399*k && yMouse>336*k){
		diff = 2;
		easy=false;
		medium=false;
		hard=true;
		engine->play2D("Tick.mp3",false);
	}

	if((options || difficulty) && state==GLUT_DOWN && xMouse<287*k && xMouse>96*k && yMouse<112*k && yMouse>49*k){      //click su BACK
		options=false;		
		difficulty=false;
		engine->play2D("Tick.mp3",false);
	}

	if(options && !how_to_play && state==GLUT_DOWN && xMouse<511*k && xMouse>319*k && yMouse<239*k && yMouse>176*k) {               //click su CONTROLS
		engine->play2D("Tick.mp3",false);
		controls=true;
	}

	if(selected7 && !controls && state==GLUT_DOWN && options && xMouse<511*k && xMouse>319*k && yMouse<366*k && yMouse>305*k){           //click su HOW TO PLAY
		engine->play2D("Tick.mp3",false);
		how_to_play=true;
	}

	if((how_to_play || controls) && state==GLUT_DOWN && xMouse<287*k && xMouse>96*k && yMouse<112*k && yMouse>49*k)        //click su BACK
	{       
		engine->play2D("Tick.mp3",false);
		how_to_play=false;
		controls=false;
		options=true;		
	}
	
	glutPostRedisplay();
}
/*
Ridisegno
*/
void MainMenu::reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.,10.,
		-10.*h/w,10.*h/w,
		-10.,10.);
}
/*
Ritorna lo stato della boolean newGame
*/
GLboolean MainMenu::isNewGame(){         
	if(newGame)
		return true;
	return false;
}
/*
Ritorna la difficolta' decisa dell'utente
*/
int MainMenu::getDiff()
{
	return diff;
}
