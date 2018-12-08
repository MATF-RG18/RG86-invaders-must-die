
#define NORTH 1
#define SOUTH -1
#define EAST 2
#define WEST -2

//ID gradjevina
#define TOWER_ID 3
#define WALL_ID 2


//KULE
struct Stower{
    int x ;
    int y ;
};

#define MAX_TOWERS 3

static struct Stower towers[MAX_TOWERS];


//f-je
void drawWall(int x1,int y1,int x2,int y2,int v);
void structDrawTower(int x,int y);
int getTowerX(int i);
int getTowerY(int i);
