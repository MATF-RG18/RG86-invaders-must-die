

//ID gradjevina

#define WALL_ID 2
#define TOWER_ID 3
#define NEXUS_ID 4
#define POST_ID 5

//max broj objekata
#define MAX_TOWERS 3
#define MAX_WALLS 3
#define MAX_POSTS 3

#define TOWER_DEMAGE 500
#define POST_DEMAGE 500
/* DEFINICIJE STRUKTURA OBJEKATA */
//KULE
struct STower{
    int x ;
    int y ;
    int healt;
    int demage;
};

//Baza
struct SNexus{
    int x;
    int y;
    int healt;
};

//Zid
struct SWall{
    int x;
    int y;
    int healt;
};

//"Cuvarski post"
struct SGuardPost{
	int x;
	int y;
	int healt;
	int demage;
};



//f-je

void initStructures();
void structPutTower(int x,int y);
int getTowerX(int i);
int getTowerY(int i);
void structPutWall(int x,int y);
int getWallX(int i);
int getWallY(int i);
void structPutPost(int x,int y);
int getPostX(int i);
int getPostY(int i);
int no_structures(int structId);

void attackOnPost(int x,int y,int demage);
void attackOnWall(int x,int y,int demage);
void attackOnTower(int x,int y,int demage);

void checkRange(int struct_id, int x,int y,int demage);


