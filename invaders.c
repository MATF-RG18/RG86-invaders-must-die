#include "invaders.h"
#include "map.h"
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include "structures.h"
#include "basic_draws.h"





#define f(x1,y1,x2,y2) ((int)((y2-y2)/(x2-x1)))
//pomocni makroi za odredjivanje pravca kretanja 
#define vx(x1,x2) (x1)-(x2) ==0?(0):(-1)
#define vy(y1,y2) (y1)-(y2) ==0?(0):(-1)

static struct STrouper troupers[MAX_TROUPERS];
static struct SEagle eagles[MAX_EAGLES];


int no_troupers = 0;
int no_eagles = 0;

//inicijalizacija 
void initInvaders(){
	no_troupers = 0;
	no_eagles = 0;
	
	int i;
	for(i=0;i<MAX_TROUPERS;i++){
		troupers[i].live = 0;
		troupers[i].x = -1;
		troupers[i].y = -1;

		troupers[i].healt = 1000;
	}
	for(i=0;i<MAX_EAGLES;i++){
		eagles[i].live = 0;
		eagles[i].x = -1;
		eagles[i].y = -1;
		eagles[i].healt = 1000;
	}
}

//postavljanje TROUPER-a na mapu
void riseTrouper(){
	if(no_troupers == MAX_TROUPERS)
		return;
	srand(time(NULL));
	int r = rand()%2;
	int s = rand()%MAP_SIZE;	
	while(!(checkFieldI(s,MAP_SIZE-1)==1 && checkFieldI(MAP_SIZE-1,s)==1)){
		s = rand()%MAP_SIZE;
	}	
	
	if(r == 1){
		troupers[no_troupers].x = MAP_SIZE-1;
		troupers[no_troupers].y = s;	
		putObject(MAP_SIZE-1,s,TROUPER_ID);		
	}
	else{
		troupers[no_troupers].x = s;
		troupers[no_troupers].y = MAP_SIZE-1;
		putObject(s,MAP_SIZE-1,TROUPER_ID);				
	}
	troupers[no_troupers].live = 1;
	no_troupers++;
}

//postavljanje EAGLE-sa na mapu
void riseEagle(){
	if(no_eagles == MAX_EAGLES)
		return;
	srand(time(NULL));
	int r = (rand()*5)%2;
	int s = rand()%MAP_SIZE;	
	while(!(checkFieldI(s,MAP_SIZE-1)==1 && checkFieldI(MAP_SIZE-1,s)==1)){
		s = rand()%MAP_SIZE;
	}	
	
	if(r == 1){
		eagles[no_eagles].x = MAP_SIZE-1;
		eagles[no_eagles].y = s;
		putObject(MAP_SIZE-1,s,EAGLE_ID);
				
	}
	else{
		eagles[no_eagles].x = s;
		eagles[no_eagles].y = MAP_SIZE-1;
		putObject(s,MAP_SIZE-1,EAGLE_ID);
		
	}
	eagles[no_eagles].live = 1;
	
	no_eagles++;

}

//dohvatanje koordinata (f-je iskljucivo namenjene iscrtavanju)

int tGetX(int id){
	return troupers[id].x;
}
int tGetY(int id){
	return troupers[id].y;
}

int eGetX(int id){
	return eagles[id].x;
}
int eGetY(int id){
	return eagles[id].y;
}

int tIsAlive(int i){
	return troupers[i].live;
}
int eIsAlive(int i){
	return eagles[i].live;
}

//F-je pomeranja Troupera i Eagle

void moveTrouper(int i){

	
	int v_x = troupers[i].x + (vx(troupers[i].x,0));
	int v_y = troupers[i].y + (vy(troupers[i].y,0));
	
	int check = checkFieldB(v_x,v_y) ;
	if( check ==1 ){
		putObject(troupers[i].x,troupers[i].y,0);
		troupers[i].x = v_x;
		troupers[i].y = v_y;		
		putObject(v_x,v_y,TROUPER_ID);

	}else{
		
		switch (check){
		
			case TOWER_ID:
				attackOnTower(v_x,v_y,TROUPER_DEMAGE);
				break;
			case WALL_ID:
				attackOnWall(v_x,v_y,TROUPER_DEMAGE);
				break;
			case POST_ID:
				attackOnPost(v_x,v_y,TROUPER_DEMAGE);
				break;
			case NEXUS_ID:
				attackOnNexus(TROUPER_DEMAGE);
				break;
		}
	}
}

void moveEagle(int i){
	int v_x = eagles[i].x + (vx(eagles[i].x,0));
	int v_y = eagles[i].y + (vy(eagles[i].y,0));
	
	int check = checkFieldB(v_x,v_y);
	if( check ==1){
		putObject(eagles[i].x,eagles[i].y,0);
		putObject(v_x,v_y,EAGLE_ID);
		eagles[i].x = v_x;
		eagles[i].y = v_y;			
	}else{
		switch (check){
			case TOWER_ID:
				attackOnTower(v_x,v_y,EAGLE_DEMAGE);
				break;
			case WALL_ID:
				attackOnWall(v_x,v_y,EAGLE_DEMAGE);
				break;
			case POST_ID:
				attackOnPost(v_x,v_y,EAGLE_DEMAGE);
				break;
			case NEXUS_ID:
				attackOnNexus(TROUPER_DEMAGE);
				break;
		}
	}
}


//main game loop
void gameLoop(){
	
	int i;
	for(i=0;i<MAX_TROUPERS;i++){
		moveTrouper(i);
	}
	for(i=0;i<MAX_EAGLES;i++){
		moveEagle(i);
	}
	for(i=0;i<MAX_TOWERS;i++){
        if(getTowerX(i) == -1)
	        continue;
	checkRange(TOWER_ID,getTowerX(i),getTowerY(i),TOWER_DEMAGE);
	}
	for(i=0;i<MAX_POSTS;i++){
        if(getPostX(i) == -1)
	        continue;
	checkRange(POST_ID,getPostX(i),getPostY(i),POST_DEMAGE);
	}

}



/*F-je za kontrolu napada na Invader-se*/
void attackTrouper(int x,int y,int demage){
	int i;
	for(i=0;i<MAX_TROUPERS;i++){
		if(troupers[i].x == x && troupers[i].y == y){
			if((troupers[i].healt -= demage) <= 0){
				putObject(troupers[i].x,troupers[i].y,0);
				troupers[i].live =0;
				troupers[i].x = -1;
				troupers[i].y = -1;
				
			}
			return;
		}

	}
}
void attackEagle(int x,int y,int demage){
	int i;
	for(i=0;i<MAX_EAGLES;i++){
		if(eagles[i].x == x && eagles[i].y == y){
			if((eagles[i].healt -= demage) <= 0){
				putObject(eagles[i].x,eagles[i].y,0);
				eagles[i].live =0;
				eagles[i].x = -1;
				eagles[i].y = -1;
				
			}
			return;		
		}
		
	}
}

