#include <GL/glut.h>
#include <stdio.h>
#include "basic_draws.h"
#include <string.h>
#include <image.h>
#include <map.h>
//IFNDEF ???


//Teksture u programu
#define MAPCOVERFILE "textures/the-prodigy_ant.bmp"
#define NEXUSCOVERFILE "textures/nexus.bmp"
#define WALLCOVERFILE "textures/wall.bmp"
#define TOWERCOVERFILE "textures/tower.bmp"
#define CANNONCOVERFILE "textures/cannon.bmp"

//Oznake za konkretne strukture u nizu
#define NO_TEXTURES 5
#define MAPTEXTURE 0
#define NEXUSTEXTURE 1
#define WALLTEXTURE 2
#define TOWERTEXTURE 3
#define CANNONTEXTURE 4

static GLuint textures[NO_TEXTURES];

//F-ja za iscrtavanje mape
void drawMap(){
	//Tekstura MAPE
    glBindTexture(GL_TEXTURE_2D,textures[MAPTEXTURE]);
        
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(1, 0);
        glVertex3f(10, 0, 0);

        glTexCoord2f(1, 1);
        glVertex3f(10, 0,10);

        glTexCoord2f(0, 1);
        glVertex3f(0, 0, 10);
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
	//Mreza polja
	int i;
    glColor3f(0,0,0);
    for(i=0;i<=MAP_SIZE;i++){
        glBegin(GL_LINES);
            glVertex3f(i,0,0);
            glVertex3f(i,0,MAP_SIZE);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(0,0,i);
            glVertex3f(MAP_SIZE,0,i);
        glEnd();
    }
    
    //iscrtavanje zemlje po obodu ostrva
    glColor3f(0.4,0.1,0);
    for(i=0;i<MAP_SIZE;i++){
            
        glPushMatrix();
        glTranslatef(i+0.5,-0.55,0.5);
        glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0.5,-0.55,i+0.5);
        glutSolidCube(1);
        glPopMatrix();
    }

}




//iscrtavanje menija
void drawMenu(int window_height,int window_width){
    
    //Menjanje matrica 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,window_width,window_height,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glClear(GL_DEPTH_BUFFER_BIT);
    
    //crtanje 2D menija
    
    float menu_width = window_height/3.0;
    float menu_height = window_width;
    print(100,100,"TExtTExtTExtTExtTExtTExtTExt");
    print(20,20,"mali text");
    
    glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(0,0);
        glVertex2f(menu_height,menu_width);
        glVertex2f(menu_height,0);
    glEnd();
    
    glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(0.0, 0.0);
        glVertex2f(window_width, 0.0);
        glVertex2f(window_width, window_height/3.0);
        glVertex2f(0.0, window_height/3.0);
    glEnd();
    

    
    //Vracanje prethodnih matrica
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
}

//iscrtavanje kule
void drawTower(int x,int y){

	int towerHeight = 2;
    
	glBindTexture(GL_TEXTURE_2D,textures[TOWERTEXTURE]);
    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(x+0.5,1,y);
    glScalef(1,towerHeight,1);
    cubeWithTexture();
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,0);

	glBindTexture(GL_TEXTURE_2D,textures[CANNONTEXTURE]);
	glPushMatrix();

	glTranslatef(x+0.5,towerHeight+0.25,y+0.25);
	glScalef(0.5,0.5,0.5);
	cubeWithTexture();
    glPopMatrix();   
	glBindTexture(GL_TEXTURE_2D,0);
}

//iscrtavanje Nexus-a(sa teksturama)
void drawNexus(){
	glBindTexture(GL_TEXTURE_2D,textures[NEXUSTEXTURE]);
	glPushMatrix();
	glTranslatef(1,0.5,0);
	glScalef(2,1,2);
	cubeWithTexture();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);
}

//iscrtavanje zida
void drawWall(int x,int y){
	glBindTexture(GL_TEXTURE_2D,textures[WALLTEXTURE]);
    glPushMatrix();
	
    glTranslatef(x+0.5,0.5,y);
    cubeWithTexture();
	
    glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,0);
}




//iscrtavanje stranice kocke sa teksturom
void cubebase(){
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);
		glVertex3d(-0.5,-0.5,0.0);
	
		glTexCoord2f(0.0,1.0);
		glVertex3d(-0.5,0.5,0.0);
		
		glTexCoord2f(1.0,1.0);
		glVertex3d(0.5,0.5,0.0);
		
		glTexCoord2f(1.0,0.0);
		glVertex3d(0.5,-0.5,0.0);
	glEnd();
}

void cubeWithTexture(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	
	//iscrtavanje osnove kocke
	cubebase();
	
	//iscrtavanje bocnih stranica
	glPushMatrix();
	glTranslated(0.5,0.0,0.5);
	glRotated(90.0,0.0,1.0,0.0);
	cubebase();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5,0.0,0.5);
	glRotated(-90.0,0.0,1.0,0.0);
	cubebase();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0,0.5,0.5);
	glRotated(-90.0,1.0,0.0,0.0);
	cubebase();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0.0,-0.5,0.5);
	glRotated(90.0,1.0,0.0,0.0);
	cubebase();
	glPopMatrix();

	//gornja stranica 
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);
		glVertex3d(-0.5,-0.5,1.0);
		
		glTexCoord2f(1.0,0.0);
		glVertex3d(0.5,-0.5,1.0);
		
		glTexCoord2f(1.0,1.0);
		glVertex3d(0.5,0.5,1.0);
		
		glTexCoord2f(0.0,1.0);
		glVertex3d(-0.5,0.5,1.0);
	glEnd();
	glPopMatrix();
	
	glFlush();
}

//F-ja za iscrtavanje igraca
void drawPlayer(int x,int y,int move){

    int px = x;
    int py = y;
    
    glPushMatrix();
    
    //rotacija karaktera u zavisnosti od pravca kretanja
    if(MOVE_LEFT == move){
        glTranslatef(px,0,py+1);
        glRotatef(90,0,1,0);
    }
    else if(MOVE_RIGHT == move){
        glTranslatef(px+1,0,py);
        glRotatef(270,0,1,0);
    }
    else if(MOVE_BACKWARD == move){
        glTranslatef(px+1,0,py+1);
        glRotatef(180,0,1,0);
    }
    else if(MOVE_FORWARD == move){
        glTranslatef(px,0,py);
    }
    
    //leva noga
    glColor3f(0, 1, 1);
    glTranslatef(0.3, 0.2, 0.5);
    glScalef(1, 2, 1);
    glutSolidCube(0.2);
 
    
    //desna noga
    glColor3f(1, 0, 1);
    glTranslatef(0.4, 0,0);
    glScalef(1, 1, 1);
    glutSolidCube(0.2);
   
    
    //trup
    glColor3f(0, 0, 1);
    glTranslatef(-0.2, 0.2, 0);
    glScalef(1,0.5,1);
    glScalef(3,2,3);
    glutSolidCube(0.2);
   
    
    //glava
    glColor3f(0, 0, 0);
    glTranslatef(0, 0.15, 0);
    glScalef(0.5,0.5,0.5);
    glutSolidCube(0.2);
    
    //lice
    glColor3f(1,1,1);
    glTranslatef(0,0,0.1);
    glutSolidSphere(0.1,20,20);
    glTranslatef(0,0,-0.1);
    
    //leva ruka
    glColor3f(1, 1, 1);
    glTranslatef(-0.25, -0.3,0);
    glScalef(0.5,1,0.5);
    glutSolidCube(0.2);

    //desna ruka
    glColor3f(1, 1, 1);
    glTranslatef(1,0,0);
    glScalef(1,1,1);
    glutSolidCube(0.2);
    
    
    glColor3f(1,1,1);
    
    glPopMatrix();
}


//F-ja za ispisivanje teksta 
void print(int x, int y, char *string)
{
    
glColor3f(1,0,0);
glRasterPos2f(x,y);

int len = (int) strlen(string);

for (int i = 0; i < len; i++)
{
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
}
}

//F-ja za inicijalizovanje tekstura programa
void initTextures(){
    
    Image *cover;
    
    glEnable(GL_TEXTURE_2D);
    
    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);
    
    cover = image_init(0, 0);
    
    image_read(cover, MAPCOVERFILE);
    glGenTextures(NO_TEXTURES, textures);
    glBindTexture(GL_TEXTURE_2D, textures[MAPTEXTURE]);
        glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 cover->width, cover->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, cover->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    image_read(cover, NEXUSCOVERFILE);
    glBindTexture(GL_TEXTURE_2D, textures[NEXUSTEXTURE]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 cover->width, cover->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, cover->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
	
	//UCITAVANJE WALL TEXTURE	
	image_read(cover, WALLCOVERFILE);
    glBindTexture(GL_TEXTURE_2D, textures[WALLTEXTURE]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 cover->width, cover->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, cover->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
	
		
	//UCITAVANJE TOWER TEXTURE	
	image_read(cover, TOWERCOVERFILE);
    glBindTexture(GL_TEXTURE_2D, textures[TOWERTEXTURE]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 cover->width, cover->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, cover->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

	
			
	//UCITAVANJE TOWER CANNON TEXTURE	
	image_read(cover, CANNONCOVERFILE);
    glBindTexture(GL_TEXTURE_2D, textures[CANNONTEXTURE]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 cover->width, cover->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, cover->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    image_done(cover);
}





