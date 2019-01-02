#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "map.h"
#include "structures.h"
#include "basic_draws.h"
#include "image.h"
#include "invaders.h"

#define UNUSED(x) ((void)x)

//timeri
#define game_timer 0
#define countdown_timer 1

//F-je pomocne
int objectX();
int objectY();

/* Dimenzije prozora */
static int window_width, window_height;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int timer_id);

static float px = 5;
static float py = 5;
static float pz = 0;
static float rot = 5;

//pomocni parametri
static int lockCamera = 0;
static int lastDirection = 0;
static int animation = 0;
static int time_left = 1000;




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
    glClearColor(0,1,1, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);

	//inicijalizacija programa
    initMapMatrix();    
    initStructures();
    initTextures();
	initInvaders();

	//glutTimerFunc(1000,on_timer,countdown_timer);
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

	// w s a d - pomeranje po mapi
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
	// SPACE dugme - u slicaju da kamera nije zakljucana pozicionira kameru na igraca
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
	case 'p':
		structPutPost(objectX(),objectY());
		on_display();
		break;
	//"zakljucavanje/otkljucavanje kamere"
    case 'c':
        if(lockCamera == 1)
            lockCamera =0;
        else 
            lockCamera = 1;
        break;
	//resetovanje postavljenih objekata
	case 'r':
		initStructures();
		initMapMatrix();
		initInvaders();
		glutPostRedisplay();
		break;
    
	case 'g':
		glutTimerFunc(1000,on_timer,countdown_timer);
		break;		
	case 'q':
		attackOnWall(3,3,1000);
		glutPostRedisplay();
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
	if(animation == 0){
		int i;		
		for(i=0;i<MAX_EAGLES;i++){
			riseEagle();
		}
		for(i=0;i<MAX_TROUPERS;i++){
			riseTrouper();	
		
		}	
		
	}	

    

	for(i=0;i<MAX_TROUPERS;i++){
		if(tIsAlive(i)){
		printf("%d : %d %d \n", i,tGetX(i),tGetY(i));
		drawTrouper(tGetX(i),tGetY(i));	
		}	
	}

    
	for(i=0;i<MAX_EAGLES;i++){
		if(eIsAlive(i)){
		printf("%d : %d %d \n", i,eGetX(i),eGetY(i));
		drawEagle(eGetX(i),eGetY(i));	
	}	
	}
	animation = 1;
	/*Iscrtavanje mape i njenih objekata*/
	drawMap();	
    drawNexus();
    drawPlayer(getX(),getY(),lastDirection);
    
    //Provera i iscrtavanje postojecih kula
    for(i=0;i<MAX_TOWERS;i++){
            if(getTowerX(i) == -1)
                continue;
            else{
                drawTower(getTowerX(i),getTowerY(i));
            }
    }
	//iscrtavanej postojecih zidova
    for(i=0;i<MAX_WALLS;i++){
            if(getWallX(i) == -1){
                continue;}
            else{
                drawWall(getWallX(i),getWallY(i));
            }
    }
	//iscrtavanje postojecih postova
	for(i=0;i<MAX_POSTS;i++){
  	       if(getPostX(i) == -1){
                continue;}
            else{
                drawPost(getPostX(i),getPostY(i));
            }
    }
    
	//checkRange(TOWER_ID,2,2,100);
    //drawTrouper(2,2);
	//drawEagle(3,3);
	
    drawMenu(window_height,window_width);
    //print(window_height-50,window_width-50,"sss");
    
	//invaders

    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
    
}
    
//za odredjivanje tacnog mesta objekta u odnosu na rotaciju igraca
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
	return -1;
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
	return -1;
}


/*timer funkcija 
	2 timera:
1. za zavrsni napad
2. odbrojavanje pred konacni napad*/
static void on_timer(int timer_id){

	if(timer_id == game_timer){
		gameLoop();
		glutPostRedisplay();
		glutTimerFunc(1000,on_timer,timer_id);
	}else if(timer_id == countdown_timer){
		time_left -=1000;
		glutPostRedisplay();
		if(time_left == 0){
			glutTimerFunc(1000,on_timer,game_timer);
		}
		else{
			glutTimerFunc(1000,on_timer,countdown_timer);
		}
	}	
	return;
}





