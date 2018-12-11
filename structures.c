#include "structures.h"
#include "map.h"
#include <stdio.h>
#include <GL/glut.h>

//inicijalno stanje objekata
int no_tower = 0;
int no_walls = 0;


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
    
    //WALLS
    for(j=0;j<MAX_WALLS;j++){
        towers[j].x = -1;
        towers[j].y = -1;
        towers[j].healt = 150;
    }
    
}


//F-je za rad sa zidovima
void structPutWall(int x,int y){
    
    if(!checkField(x,y))
        return;
    if(no_walls == MAX_WALLS)
        return;
    walls[no_walls].x = x;
    walls[no_walls].y = y;
    putObject(x,y,WALL_ID);
    no_walls++;
}

int getWallX(int i){
    return walls[i].x;
}
int getWallY(int i){
    return walls[i].y;
}




//F-je sa kulama
void structPutTower(int x,int y){
    if(!checkField(x,y))
        return;
    if(no_tower == MAX_TOWERS)
        return;
    towers[no_tower].x = x;
    towers[no_tower].y = y;
    putObject(x,y,TOWER_ID);
    no_tower++;
}

int getTowerX(int i){
    return towers[i].x;
}
int getTowerY(int i){
    return towers[i].y;
}


