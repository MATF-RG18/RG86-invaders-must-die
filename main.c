#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "map.h"
#include "structures.h"
#include "basic_draws.h"


#define UNUSED(x) ((void)x)
/* Dimenzije prozora */
static int window_width, window_height;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

static float px = 5;
static float py = 5;
static float pz = 0;
static float rot = 5;

static int lockCamera = 0;
static int lastDirection = 0;



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
    
    initStructures();

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();
    return 0;
}




static void on_keyboard(unsigned char key, int x, int y)
{
    UNUSED(x);
    UNUSED(y);
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
        lastDirection = MOVE_RIGHT;
        on_display();
        break;
    case 'a':
        mapMovePlayer(1,0);
        lastDirection = MOVE_LEFT;
        on_display();
        break;
    case 'w':
        mapMovePlayer(0,1);
        lastDirection = MOVE_FORWARD;
        on_display();
        break;
    case 's':
        mapMovePlayer(0,-1);
        lastDirection = MOVE_BACKWARD;
        on_display();
        break;
    case 32:
        pz = getY()-4;
        rot = getX();
        px = getX() -1;
        on_display();
        break;
    case 't':
        structPutTower(objectX(),objectY());
        on_display();
        break;
    case 'z':
        structPutWall(objectX(),objectY());
        on_display();
        break;
    case 'c':
        if(lockCamera == 1)
            lockCamera =0;
        else 
            lockCamera = 1;
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
            0.2, 50);

   
    /* Podesava se tacka pogleda. */
        
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
        if (lockCamera == 1){
            pz = getY()-4;
            rot = getX();
            px = getX() -1;
        }
    	gluLookAt(
            px,py,pz,
            rot, 0,MAP_SIZE,
            0, 1, 0
        );


    /*glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(.5, 1, 0);
    glScalef(1, 2, 1);
    glutSolidCube(1);
    glPopMatrix();*/
    
    drawNexus();
    
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
    int i;
    
    
    glColor3f(0,1,1);
        glBegin(GL_POLYGON);
        glVertex3f(-25,-1,-25);
        glVertex3f(-25,-1,25);
        glVertex3f(100,-1,25);
        glVertex3f(100,-1,-25);
    glEnd();
    glColor3f(0,1,1);
    glBegin(GL_POLYGON);
        glVertex3f(100,-1,20);
        glVertex3f(-100,-1,20);
        glVertex3f(-100,100,20);
        glVertex3f(100,100,20);
    glEnd();
    //mapa iscrtavanje
    
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(0,0,0);
        glVertex3f(0,0,MAP_SIZE);
        glVertex3f(MAP_SIZE,0,MAP_SIZE);
        glVertex3f(MAP_SIZE,0,0);
    glEnd();
    
    //Mreza polja
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
    
    //iscrtavanje zemlje po obodu ostrva
    glColor3f(0.4,0.1,0);
    for(i=0;i<MAP_SIZE;i++){
            
        glPushMatrix();
        glTranslatef(i+0.5,-0.55,0.5);
        glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0.5,-0.55,i+0.5);
        glutSolidCube(1);
        glPopMatrix();
    }
    
    
    
    drawPlayer(getX(),getY(),lastDirection);
    //drawWall(4,4,8,4,NORTH);
    //drawWall(6,6,9,6,NORTH);
    //structDrawTower(2,2);
    
    //Provera i iscrtavanje postojecih kula
    for(i=0;i<MAX_TOWERS;i++){
            if(getTowerX(i) == -1)
                break;
            else{
                drawTower(getTowerX(i),getTowerY(i));
            }
    }
    for(i=0;i<MAX_WALLS;i++){
            if(getWallX(i) == -1)
                break;
            else{
                drawWall(getWallX(i),getWallY(i));
            }
    }
    
    drawMenu(window_height,window_width);
    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

int objectX(){
    switch (lastDirection){
        case 0:
            return getX();
        case 1:
            return getX()+1;
        case 2:
            return getX();
        case 3:
            return getX() -1;
    }
}
int objectY(){
    switch (lastDirection){
        case 0:
            return getY()+1;
        case 1:
            return getY();
        case 2:
            return getY()-1;
        case 3:
            return getY();
    }
}





