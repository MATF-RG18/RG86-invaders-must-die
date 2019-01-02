#define MAP_SIZE 10

void initMapMatrix(void);

int getX();
int getY();

void putObject(int x,int y,int objectType);
void mapMovePlayer(int x,int y);
int checkField(int i,int j);
