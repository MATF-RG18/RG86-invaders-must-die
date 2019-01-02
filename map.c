#include <stdio.h>
#include "map.h"
#include "structures.h"

//pocetne koordinate igraca
int plx = 2;
int ply = 2;
int plz = 0;

//matrica mape
static int map_matrix [MAP_SIZE][MAP_SIZE];

//inicijalizacija mape
void initMapMatrix(void){
    int i,j;
    for(i=0;i<MAP_SIZE;i++){
     for(j=0;j<MAP_SIZE;j++){
            map_matrix[i][j] = 0;
         }
    }
    map_matrix[0][0] = NEXUS_ID;
	map_matrix[1][0] = NEXUS_ID;
    map_matrix[1][1] = NEXUS_ID;
    map_matrix[0][1] = NEXUS_ID;
    for(i=0;i<MAP_SIZE;i++){
     for(j=0;j<MAP_SIZE;j++){
            printf("%d ",map_matrix[i][j]);
         }
         printf("\n");
    }
    
    printf("###########################\n");
}


//dohvatanje igracevih koordinata
int getX(){
    return plx;
}
int getY(){
    return ply;
}

//postavljanje onjekta na mapu, svaki objekat je jedinstveno odredjen svojim ID-om
void putObject(int x,int y,int objectType){
    map_matrix[x][y] = objectType;
    
}


//kontrola i pometanje igraca
void mapMovePlayer(int x,int y){
    int i,j;
    
    if(plx+x == MAP_SIZE || ply+y == MAP_SIZE || plx+x < 0 || ply+y <0)
        return;
    if(map_matrix[plx+x][ply+y] != 0)
        return;
    map_matrix[plx][ply] = 0;
    plx+= x;
    ply+=y;
    map_matrix[plx][ply] = 1;
    
    for(i=0;i<MAP_SIZE;i++){
     for(j=0;j<MAP_SIZE;j++){
            printf("%d ",map_matrix[i][j]);
         }
         printf("\n");
    }
    printf("###########################\n");
}


//provera da li je polje prazno ili ne
int checkField(int i,int j){
   if(i >= MAP_SIZE || j>= MAP_SIZE || i<0 || j<0){
       return 0;
	}
	else if(map_matrix[i][j] != 0)
		return map_matrix[i][j];
	else
   		return 0==map_matrix[i][j]; 
}
