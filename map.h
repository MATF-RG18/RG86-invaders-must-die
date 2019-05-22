#define MAP_SIZE 12

//inicijalizacija
void initMapMatrix(void);

//koordinate igraca
int getX();
int getY();


void putObject(int x,int y,int objectType);
void mapMovePlayer(int x,int y);
void prepareForAttack();

//provera polja
int checkFieldB(int i,int j);
int checkFieldI(int i,int j);
