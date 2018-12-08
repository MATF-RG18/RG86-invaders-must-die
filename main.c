#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "map.h"
#include "structures.h"

/* Dimenzije prozora */
static int window_width, window_height;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

static float px = 5;
static float py = 5;
static float pz = 0;
static int vpx = 1;
static int vpy = 0.5;
static int vpz = 1;
static float rot = 5;
static tower = 0;

void drawPlayer(int x, int y);


int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    //glutPostRedisplay(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
    initMapMatrix();
    

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();
    return 0;
}




static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
    /*case 'd':
        px +=0.2;
	on_display();
	
	break;
    case 'a':
	px-=0.2;
	on_display();
	break;
    case 'w':
	pz-=0.2;
	on_display();
	break;
    case 's':
	pz+=0.2;
	on_display();
	break;*/
    case 'd':
        mapMovePlayer(-1,0);
        on_display();
        break;
    case 'a':
        mapMovePlayer(1,0);
        on_display();
        break;
    case 'w':
        mapMovePlayer(0,1);
        on_display();
        break;
    case 's':
        mapMovePlayer(0,-1);
        on_display();
        break;
    case 32:
        pz = getY()-4;
        rot = getX();
        px = getX() -1;
        on_display();
        break;
    case 't':
        structDrawTower(getX(),getY()+1);
        on_display();
        break;
    }
}


static void on_reshape(int width, int height)
{
    /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se viewport. */
    glViewport(0, 0, window_width, window_height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            90,
            window_width/(float)window_height,
            0.2, 25);

   
    /* Podesava se tacka pogleda. */
        
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
    	gluLookAt(
            px,py,pz,
            rot, 0,MAP_SIZE,
            0, 1, 0
        );

    /*
     * Kreira se kocka i primenjuje se geometrijska transformacija na
     * istu.
     */
    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(.5, 1, 0);
    glScalef(1, 2, 1);
    glutSolidCube(1);
    
    glPopMatrix();
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
    glEnd();
    int i,j;
    
    //mapa iscrtavanje
    
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(0,0,0);
        glVertex3f(0,0,MAP_SIZE);
        glVertex3f(MAP_SIZE,0,MAP_SIZE);
        glVertex3f(MAP_SIZE,0,0);
    glEnd();
    
    glColor3f(0,0,0);
    for(i=0;i<=MAP_SIZE;i++){
        glBegin(GL_LINES);
            glVertex3f(i,0,0);
            glVertex3f(i,0,MAP_SIZE);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(0,0,i);
            glVertex3f(MAP_SIZE,0,i);
        glEnd();
    }
    

    drawPlayer(getX(),getY());
    drawWall(4,4,8,4,NORTH);
    drawWall(6,6,9,6,NORTH);
    //structDrawTower(2,2);
    
    for(i=0;i<MAX_TOWERS;i++){
            if(getTowerX(i) == -1)
                break;
            else{
                drawTower(getTowerX(i),getTowerY(i));
            }
    }
    
  /*  int i,j;
    for(i=0;i<MAP_SIZE;i++)
        for(j=0;j<MAP_SIZE;j++)
            if(map_*/
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}


//F-ja za iscrtavanje igraca
void drawPlayer(int x,int y){
    
    int px = getX();
    int py = getY();
    
   
    
    glPushMatrix();
    glColor3f(0, 1, 1);
    glTranslatef(px+0.3, 0.2, py+0.5);
    glScalef(1, 2, 1);
    glutSolidCube(0.2);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(px+0.7, 0.2, py+0.5);
    glScalef(1, 2, 1);
    glutSolidCube(0.2);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(px+0.5, 0.6, py+0.5);
    glScalef(3,2,3);
    glutSolidCube(0.2);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 1);
    glTranslatef(px+0.5, 0.9, py+0.5);
    glScalef(1,1,1);
    glutSolidCube(0.2);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 1);
    glTranslatef(px+0.1, 0.60, py+0.5);
    glScalef(1,1.5,1);
    glutSolidCube(0.2);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 1);
    glTranslatef(px+0.9, 0.60, py+0.5);
    glScalef(1,1.5,1);
    glutSolidCube(0.2);
    glPopMatrix();
}

void drawTower(int x,int y){
    int towerHeight = 3;
    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(x+0.5,1.5,y+0.5);
    glScalef(1,towerHeight,1);
    glutWireCube(1);
    glPopMatrix();   
}



