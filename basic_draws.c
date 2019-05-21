#include <GL/glut.h>
#include <stdio.h>
#include "basic_draws.h"
#include <string.h>
#include <image.h>
#include <map.h>
#include <stdlib.h>
#include <structures.h>
#include "invaders.h"
//IFNDEF ???


//Teksture u programu
#define MAPCOVERFILE "textures/the-prodigy_ant.bmp"
#define NEXUSCOVERFILE "textures/nexus.bmp"
#define WALLCOVERFILE "textures/wall.bmp"
#define TOWERCOVERFILE "textures/tower.bmp"
#define CANNONCOVERFILE "textures/cannon.bmp"
#define CANNONCOVERFILE2 "textures/cannon_top.bmp"
#define POSTCOVERFILE "textures/post.bmp"
#define POSTCOVERFILE2 "textures/post_top.bmp"
#define TANKTEXTUREFILE1 "textures/tank.bmp"

//Oznake za konkretne strukture u nizu
#define NO_TEXTURES 9
#define MAPTEXTURE 0
#define NEXUSTEXTURE 1
#define WALLTEXTURE 2
#define TOWERTEXTURE 3
#define CANNONTEXTURE 4
#define CANNONTEXTURE2 5
#define POSTTEXTURE 6
#define POSTTEXTURE2 7
#define TANKTEXTURE1 8
static GLuint textures[NO_TEXTURES];

static char finalMsg = 0;

//F-ja za iscrtavanje mape
void drawMap(){
	//Tekstura MAPE
    glBindTexture(GL_TEXTURE_2D,textures[MAPTEXTURE]);
        
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(1, 0);
        glVertex3f(MAP_SIZE-1, 0, 0);

        glTexCoord2f(1, 1);
        glVertex3f(MAP_SIZE-1, 0,MAP_SIZE-1);

        glTexCoord2f(0, 1);
        glVertex3f(0, 0, MAP_SIZE-1);
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
	//Mreza polja
	int i;
    glColor3f(0,0,0);
    for(i=0;i<=MAP_SIZE-1;i++){
        glBegin(GL_LINES);
            glVertex3f(i,0,0);
            glVertex3f(i,0,MAP_SIZE-1);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(0,0,i);
            glVertex3f(MAP_SIZE-1,0,i);
        glEnd();
    }
    
    //iscrtavanje zemlje po obodu ostrva
    glColor3f(0.4,0.1,0);
    for(i=0;i<MAP_SIZE-1;i++){
            
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
void drawMenu(){
    
	int width = 600;
	int height = 600;

    //Menjanje matrica 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,width,height,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glClear(GL_DEPTH_BUFFER_BIT);
    
    //crtanje 2D menija
    
    float menu_width = width;
    float menu_height = height/4.0;

 
	char buffer[50];
	if(finalMsg == 0){
	sprintf(buffer,"Broj preostalih kula: %d",no_structures(TOWER_ID));
	print(menu_width/2+50,30,buffer);
	sprintf(buffer,"Broj preostalih zidova: %d",no_structures(WALL_ID));
	print(menu_width/2+50,50,buffer);	
	sprintf(buffer,"Broj preostalih postova: %d",no_structures(POST_ID));
	print(menu_width/2+50,70,buffer);

	print(10,30,"Da postavite kulu - 't'");
	print(10,50,"Da postavite zid - 'z'");
	print(10,70,"Da postavite post - 'p'");
	print(10,90,"Zakljucavanje kamere - 'c'");
	print(10,110,"Da pozicionirate kameru na sebe - 'SPACE'");
	print(10,130,"Za pocetak napada - 'f'");
}
	else if (finalMsg == 1){
		print(200,40,"###########################");
		print(200,60,"###        WIN          ###");		
		print(200,80,"###########################");
	} 
	else if (finalMsg == -1){
		print(200,40,"###########################");
		print(200,60,"###      GAME OVER      ###");		
		print(200,80,"###########################");
	} 

	//print(menu_width-250,170,"Napomena: objekat se postavlja");
	//print(menu_width-250,205,"postavlja u na polje ispred igraca");	
    //print(menu_width-250,240,"igraca. ");
    /*glBegin(GL_LINES);
    	glLineWidth(4);
        glColor3f(0,0,0);
		glVertex2f(menu_width/2,0);
		glVertex2f(menu_width/2,menu_height);
    glEnd();
    */
    glBegin(GL_QUADS);
        glColor3f(0.8,0.7,0.1);
        glVertex2f(0.0, 0.0);
        glVertex2f(width, 0.0);
        glVertex2f(width, menu_height);
        glVertex2f(0.0, height/4.0);
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
    cubeWithTexture(0);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,0);

	glBindTexture(GL_TEXTURE_2D,textures[CANNONTEXTURE]);
	glPushMatrix();

	glTranslatef(x+0.5,towerHeight+0.25,y+0.25);
	glScalef(0.5,0.5,0.5);
	cubeWithTexture(CANNONTEXTURE2);
    glPopMatrix();   
	glBindTexture(GL_TEXTURE_2D,0);
}

//iscrtavanje Nexus-a(sa teksturama)
void drawNexus(){
	glBindTexture(GL_TEXTURE_2D,textures[NEXUSTEXTURE]);
	glPushMatrix();
	glTranslatef(1,0.5,0);
	glScalef(2,1,2);
	cubeWithTexture(0);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);
}

//iscrtavanje zida
void drawWall(int x,int y){
    glBindTexture(GL_TEXTURE_2D,textures[WALLTEXTURE]);
    glPushMatrix();
	
    glTranslatef(x+0.5,0.5,y);
    cubeWithTexture(0);
	
    glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,0);
}



//Iscrtavanje "Cuvarskog posta"

void drawPost(int x,int y){
    glBindTexture(GL_TEXTURE_2D,textures[POSTTEXTURE]);
    glPushMatrix();
	
    glTranslatef(x+0.5,0.5,y);
    cubeWithTexture(POSTTEXTURE2);
	
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

void cubeWithTexture(int diff_top){
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
	glTranslated(0.0,-0.5,0.5);
	glRotated(90.0,1.0,0.0,0.0);
	cubebase();
	glPopMatrix();

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
	
	//u slucaju da gornja stranica nema istu teksturu 
	if(diff_top != 0){
		glBindTexture(GL_TEXTURE_2D,0);
		glBindTexture(GL_TEXTURE_2D,textures[diff_top]);
	}		

	//gornja
	glPushMatrix();
	glTranslated(0.0,0.5,0.5);
	glRotated(-90.0,1.0,0.0,0.0);
	cubebase();
	glPopMatrix();
	
	
	glFlush();
}

/*Iscrtavanje invadersa*/

//Trouper

void drawTrouper(int x,int y){
    
	
    glBindTexture(GL_TEXTURE_2D,textures[TANKTEXTURE1]);	
    glPushMatrix();
	glColor3f(0,0,0);
    glTranslatef(x+0.35,0.5,y);
    glScalef(0.5,0.5,0.5);
    cubeWithTexture(0);
    glPopMatrix();
	
	glPushMatrix();
	glColor3f(0,0,0);
        glTranslatef(x+0.5,0.75,y+0.5);
        glScalef(0.25,0.25,0.25);
        cubeWithTexture(0);
	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D,0);
        
}

//Eagle

void drawEagle(int x,int y){
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(x+0.5,1.5,y+0.5);
	//glRotatef(45,1,0,0);
	glutSolidCube(0.5);		
	glPopMatrix();

}


void drawCabbine(){

	glPushMatrix();
	glTranslatef(0.5,3,0.5);
	glutWireCube(1);
	glPopMatrix();


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


void endGame(char result){
	if (result == 1){
			finalMsg = 1;
			drawMenu();
	}
	else if (result == -1){
		finalMsg = -1;
		drawMenu();
	}
		
}




//F-ja za ispisivanje teksta 
void print(int x, int y, char *string)
{



int len = (int) strlen(string);
int l =0; 
int i;
for(i=0;i<len;i++)
	l +=glutBitmapWidth(GLUT_BITMAP_9_BY_15,string[i]);
	
glColor3f(0,0,0);
glRasterPos2f(x,y);

for (i = 0; i < len; i++)
{
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,string[i]);
}
//printf("%d \n",l);
}

//F-ja za inicijalizovanje tekstura programa
void initTextures(){
    
    Image *cover;
    
    glEnable(GL_TEXTURE_2D);
    
    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);
    
    cover = image_init(0, 0);
    
	//ucitavanje MAP TEXTURE
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
	
	//ucitavanje NEXUS TEXTURE    
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


			
	//UCITAVANJE TOWER CANNON TEXTURE TOP SIDE	
	image_read(cover, CANNONCOVERFILE2);
    glBindTexture(GL_TEXTURE_2D, textures[CANNONTEXTURE2]);
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





	//Tekstura "Cuvarskog posta"
	image_read(cover, POSTCOVERFILE);
    glBindTexture(GL_TEXTURE_2D, textures[POSTTEXTURE]);
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
	
	
	//Tekstura "Cuvarskog posta"
	image_read(cover, POSTCOVERFILE2);
    glBindTexture(GL_TEXTURE_2D, textures[POSTTEXTURE2]);
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

    	//Tekstura "Cuvarskog posta"
	image_read(cover, TANKTEXTUREFILE1);
    glBindTexture(GL_TEXTURE_2D, textures[TANKTEXTURE1]);
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



