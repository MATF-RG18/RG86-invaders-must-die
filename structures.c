#include "structures.h"
#include "map.h"
#include <stdio.h>
#include <GL/glut.h>

int no_tower = 0;


//f-ja za inicijalizaciju 
void initStructures(){
    
    //niz kula
    int j;
    for(j=0;j<MAX_TOWERS;j++){
        towers[j].x = -1;
        towers[j].y = -1;
        towers[j].healt = 100;
        towers[j].demage = 20;
    }
    
    //NEXUS
    Nexus.x = 0;
    Nexus.y = 0;
    Nexus.healt = 500;
    
}


void drawWall(int x1,int y1,int x2,int y2,int v){
    
    int height = 1;
    glPushMatrix();
    glTranslatef(x1+(float)(x2-x1)/2,0.5,y1+0.5);
    glScalef(x2-x1,1,1);
    glutSolidCube(1);
    glPopMatrix();
    putObject(x1,y1,WALL_ID,NORTH,x2-x1);
}





//F-je sa kulama
void structDrawTower(int x,int y){
    if(!checkField(x,y))
        return;
    if(no_tower == MAX_TOWERS)
        return;
    towers[no_tower].x = x;
    towers[no_tower].y = y;
    printf("%d %d\n",towers[no_tower].x, towers[no_tower].y);
    putObject(x,y,TOWER_ID,-1,1);
    no_tower++;
}

int getTowerX(int i){
    return towers[i].x;
}
int getTowerY(int i){
    return towers[i].y;
}