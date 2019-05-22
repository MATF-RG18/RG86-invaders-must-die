#include "structures.h"
#include "map.h"
#include <stdio.h>
#include <GL/glut.h>
#include "invaders.h"


//inicijalni nizovi 
static struct SNexus Nexus;
static struct STower towers[MAX_TOWERS];
static struct SWall walls[MAX_WALLS];
static struct SGuardPost posts[MAX_POSTS];


//inicijalno stanje objekata
int no_towers = 0;
int no_walls = 0;
int no_posts = 0;

//f-ja za inicijalizaciju 
void initStructures(){
    
	no_towers = 0;
	no_walls = 0;
	no_posts = 0;
    //niz kula
    int j;
    for(j=0;j<MAX_TOWERS;j++){
        towers[j].x = -1;
        towers[j].y = -1;
        towers[j].healt = 100;
        towers[j].demage = 500;
    }
    
    //NEXUS
    Nexus.x = 0;
    Nexus.y = 0;
    Nexus.healt = 200;
    
    //WALLS
    for(j=0;j<MAX_WALLS;j++){
        walls[j].x = -1;
        walls[j].y = -1;
        walls[j].healt = 200;
    }

    //POSTS
    for(j=0;j<MAX_POSTS;j++){
        posts[j].x = -1;
        posts[j].y = -1;
        posts[j].healt = 100;
	posts[j].demage = 500;
    }


}


//F-je za rad sa zidovima
void structPutWall(int x,int y){
    
    if(checkFieldB(x,y)!=1)
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
    if(checkFieldB(x,y)!=1)
        return;
    if(no_towers == MAX_TOWERS)
        return;
    towers[no_towers].x = x;
    towers[no_towers].y = y;
    putObject(x,y,TOWER_ID);
    no_towers++;
}

int getTowerX(int i){
    return towers[i].x;
}
int getTowerY(int i){
    return towers[i].y;
}


//F-je za rad sa "cuvarskim postovima"
void structPutPost(int x,int y){
    
    if(checkFieldB(x,y)!=1)
        return;
    if(no_posts == MAX_POSTS)
        return;
    posts[no_posts].x = x;
    posts[no_posts].y = y;
    putObject(x,y,POST_ID);
    no_posts++;
}

int getPostX(int i){
    return posts[i].x;
}
int getPostY(int i){
    return posts[i].y;
}

//pomocna funkcija za ispis u meni
int no_structures(int structId){

	switch(structId){
		case TOWER_ID:
			return MAX_TOWERS - no_towers;
		break;
		case WALL_ID:
			return MAX_WALLS - no_walls;
		break;
		case POST_ID:
			return MAX_POSTS - no_posts;
		break;	
	
	}
	return 0;
}


/*F-je koje obradjuju napade na objekte*/
void attackOnPost(int x,int y,int demage){
	int i;
	for(i=0;i<MAX_POSTS;i++){
		if(posts[i].x == x && posts[i].y == y){
			if((posts[i].healt -= demage) <=0){
				putObject(posts[i].x, posts[i].y,0);
				posts[i].x = -1;
				posts[i].y = -1;
				
			}
			return;
		}
	}
}

void attackOnWall(int x,int y,int demage){
	int i;
	for(i=0;i<MAX_WALLS;i++){
		if(walls[i].x == x && walls[i].y == y){
			if((walls[i].healt -= demage) <=0){
				putObject(walls[i].x, walls[i].y,0);
				walls[i].x = -1;
				walls[i].y = -1;
				
			}
			return;
		}
	}
	
}

void attackOnTower(int x,int y,int demage){
	int i;
	for(i=0;i<MAX_TOWERS;i++){
		if(towers[i].x == x && towers[i].y == y){
			if((towers[i].healt -= demage) <=0){
				putObject(towers[i].x, towers[i].y,0);
				towers[i].x = -1;
				towers[i].y = -1;
			}
			return;
		}
	}
}

void attackOnNexus(int demage){

	Nexus.healt -= demage;

}


//F-je za pracenje stanja igre
char checkGame(){

	if(Nexus.healt<=0){
		return -1;
	}
	else{
		char has_survivors = 0;
		int i;
		for(i=0;i<MAX_TROUPERS;i++){
			if(tIsAlive(i) != 0){
				has_survivors = 1;
				break;
			}
		}
		if(has_survivors == 0){
			for(i=0;i<MAX_EAGLES;i++){
				if(eIsAlive(i) != 0){
					has_survivors = 1;
					break;
				}
			}
		}

		return !has_survivors;
	}
}

void checkRange(int struct_id,int x,int y, int demage){
	
	int i,j;
	if(struct_id == TOWER_ID){
			
		for(i=-1;i<2;i++){
			for(j=-1;j<2;j++){
				if(checkFieldB(x+i,y+j) == EAGLE_ID){
					attackEagle(x+i,y+j,demage);
					return;
				}			
			}
		}
	}
	else if(struct_id == POST_ID){
		for(i=-1;i<2;i++){
			for(j=-1;j<2;j++){
				/*if(checkFieldB(x+i,y+j) == EAGLE_ID){
					attackEagle(x+i,y+j,demage);*/
				if(checkFieldB(x+i,y+j) == TROUPER_ID){
					attackTrouper(x+i,y+j,demage);
				}
			}
		}
	}
}


