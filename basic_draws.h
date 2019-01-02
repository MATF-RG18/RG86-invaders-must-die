
#define MOVE_LEFT 1
#define MOVE_RIGHT 3
#define MOVE_FORWARD 0
#define MOVE_BACKWARD 2




void drawMenu(int window_height,int window_width);
void drawTower(int x,int y);
void drawNexus();
void drawPlayer(int x,int y,int move);
void drawWall(int x,int y);
void print(int x, int y, char *string);
void cubebase();
void cubeWithTexture(int diff_top);
void initTextures();
void drawMap();
void drawPost(int x,int y);
void drawTrouper(int x,int y);
void drawEagle(int x,int y);
void trouperAttack(int x1,int y1,int x2,int y2,int id);
