#define MAP_SIZE 10
static int map_matrix [MAP_SIZE][MAP_SIZE];

void initMapMatrix(void);

int getX();
int getY();

void putObject(int x,int y,int objectType,int v,int d);
void mapMovePlayer(int x,int y);
int checkField(int i,int j);
