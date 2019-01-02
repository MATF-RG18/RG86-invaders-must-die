
//Invaders id's

#define TROUPER_ID 15
#define EAGLE_ID 16


#define MAX_TROUPERS 3
#define MAX_EAGLES 3


#define DOWN -1
#define RIGHT 1
#define RIGHTDOWN 0
#define ATTACK 2

#define TROUPER_DEMAGE 60
#define EAGLE_DEMAGE 60


//Definicije struktura Invaders-a
struct STrouper{
	int x;
	int y;
	int healt;
	char live;

	
};

struct SEagle{
	int x;
	int y;
	int healt;
	char live;
};


void initInvaders();
int demageTaken(int power,char target,int i);
int tGetX(int id);
int tGetY(int id);
int eGetX(int id);
int eGetY(int id);
int tIsAlive(int i);
int eIsAlive(int i);
void riseTrouper();
void riseEagle();
void attackTrouper(int x,int y,int demage);
void attackEagle(int x,int y,int demage);


void gameLoop();

