#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "map.h"
#include "structures.h"
#include "basic_draws.h"
#include "image.h"

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
    glClearColor(0, 1,1, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
    initMapMatrix();
    
    initStructures();
    initTextures();

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
	case 'r':
		initStructures();
		initMapMatrix();
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



    int i;

	/*Iscrtavanje mape i njenih objekata*/
	drawMap();	
    drawNexus();
    drawPlayer(getX(),getY(),lastDirection);
    
    //Provera i iscrtavanje postojecih kula
    for(i=0;i<MAX_TOWERS;i++){
            if(getTowerX(i) == -1)
                break;
            else{
                drawTower(getTowerX(i),getTowerY(i));
            }
    }
	
    for(i=0;i<MAX_WALLS;i++){
            if(getWallX(i) == -1){
                break;}
            else{
                drawWall(getWallX(i),getWallY(i));
            }
    }
    
    drawMenu(window_height,window_width);
    print(20,20,"ISa");
    
    
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






