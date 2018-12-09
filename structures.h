
#define NORTH 1
#define SOUTH -1
#define EAST 2
#define WEST -2

//ID gradjevina

#define WALL_ID 2
#define TOWER_ID 3
#define NEXUS_ID 4

//max broj objekata
#define MAX_TOWERS 3


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


static struct SNexus Nexus;
static struct STower towers[MAX_TOWERS];


//f-je
void drawWall(int x1,int y1,int x2,int y2,int v);
void structDrawTower(int x,int y);
int getTowerX(int i);
int getTowerY(int i);
void initStructures();
