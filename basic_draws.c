#include <GL/glut.h>
#include <stdio.h>
#include "basic_draws.h"
//IFNDEF ???


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
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);
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
    int towerHeight = 3;
    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(x+0.5,1.5,y+0.5);
    glScalef(1,towerHeight,1);
    glutSolidCube(1);
    glPopMatrix();   
}

//iscrtavanje Nexus-a
void drawNexus(){
    glPushMatrix();
    glColor3f(0.1,0.5,1);
    glTranslatef(1,0.5,1);
    glScalef(2,1,2);
    glutSolidCube(1);
    glPopMatrix();
}

void drawWall(int x,int y){
    glColor3f(0.7,0.3,0);
    glPushMatrix();
    glTranslatef(x+0.5,0.5,y+0.5);
    glutSolidCube(1);
    glPopMatrix();
}

//F-ja za iscrtavanje igraca
void drawPlayer(int x,int y,int move){

    int px = x;
    int py = y;
    
    
    glPushMatrix();
    //leva noga
    
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
    glColor3f(0, 1, 1);
    glTranslatef(0.3, 0.2, 0.5);
//    glTranslatef(px+0.3, 0.2, py+0.5);
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

