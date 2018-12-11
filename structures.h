

//ID gradjevina

#define WALL_ID 2
#define TOWER_ID 3
#define NEXUS_ID 4

//max broj objekata
#define MAX_TOWERS 3
#define MAX_WALLS 3

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

struct SWall{
    int x;
    int y;
    int healt;
};

static struct SNexus Nexus;
static struct STower towers[MAX_TOWERS];
static struct SWall walls[MAX_WALLS];


//f-je
void structPutWall(int x,int y);
void structPutTower(int x,int y);
int getTowerX(int i);
int getTowerY(int i);
int getWallX(int i);
int getWallY(int i);
void initStructures();
