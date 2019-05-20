#define MAP_SIZE 12

void initMapMatrix(void);

int getX();
int getY();

void putObject(int x,int y,int objectType);
void mapMovePlayer(int x,int y);
int checkFieldB(int i,int j);
void prepareForAttack();
int checkFieldI(int i,int j);
