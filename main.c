#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "map.h"
#include "structures.h"
#include "basic_draws.h"
#include "image.h"
#include "invaders.h"
#include <math.h>
#define UNUSED(x) ((void)x)

//timeri
#define game_timer 0
#define countdown_timer 1

#define PI 3.14159265

//F-je pomocne
int objectX();
int objectY();

/* Dimenzije prozora */


/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int timer_id);

static float px = 5;
static float py = 5;
static float pz = 0;
static float rot = MAP_SIZE /2;

//pomocni parametri
static int lockCamera = 0;
static int lastDirection = 0;
static int animation = 0;
static short final_attack =0;
static short end = 0;
static int time_left = 2;


static float final_x = 0;
static float final_y = 0;



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
    unsigned char k;
    if(final_attack){
        if(key != 27 && key != 32){
            k = 0;
        }
        else{
            k = key;
        }
    }else{
        k = key;
    }
    switch (k) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

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
            break;
            
    //DEBUG 
    case 'q':
		attackOnWall(3,3,1000);
		glutPostRedisplay();
		break;	
	
    case 'f':
        glutTimerFunc(1000,on_timer,countdown_timer);
        break;

    }
    }


//prilikom pokusaja da se promeni velicina prozora, ista se ne menja
static void on_reshape(int width, int height)
{
	UNUSED(width);
	UNUSED(height);
	//f-ja koja postavlja velicinu prozora
	glutReshapeWindow(800,600);
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se viewport. */
    glViewport(0, 0, 800, 600);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            90,
            800/(float)600,
            0.2, 50);

   
    /* Podesava se tacka pogleda. */
        
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
        if (lockCamera == 1){
            pz = getY()-4;
            rot = getX();
            px = getX() -1 ;
        }
    	gluLookAt(
            px,py,pz,
            rot, 0,MAP_SIZE,
            0, 1, 0
        );


    int i;
	if(animation == 1){
		int i;		
		for(i=0;i<MAX_EAGLES;i++){
			riseEagle();
		}
		for(i=0;i<MAX_TROUPERS;i++){
			riseTrouper();	
		
		}
		animation = 0;	
		
	}	

    

	for(i=0;i<MAX_TROUPERS;i++){
		if(tIsAlive(i)){
		//printf("%d : %d %d \n", i,tGetX(i),tGetY(i));
		drawTrouper(tGetX(i),tGetY(i));	
		}	
	}

    
	for(i=0;i<MAX_EAGLES;i++){
		if(eIsAlive(i)){
		//printf("%d : %d %d \n", i,eGetX(i),eGetY(i));
		drawEagle(eGetX(i),eGetY(i));	
	}	
	}

	/*Iscrtavanje mape i njenih objekata*/
	drawMap();	
    drawNexus();
    if(final_attack == 0){
    drawPlayer(getX(),getY(),lastDirection);
    
    }
    else{
        glPushMatrix();
        glTranslatef(0,1,0);
        drawPlayer(final_x,final_y,0);
        glPopMatrix();
    }
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
	
    drawMenu();
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
		
		end = checkGame();
		if(end != 0){
			printf("end:%d\n",end);
			endGame(end);		
		}else{
			glutTimerFunc(1000,on_timer,timer_id);
		}
	}else if(timer_id == countdown_timer){
		time_left -=1;
		glutPostRedisplay();
		if(time_left == 0){
			glutTimerFunc(1000,on_timer,game_timer);
                        final_attack = 1;
                        prepareForAttack();
                        lockCamera = 0;
						px = -1;
						pz = -4;
                    
                }
		else{
			animation = 1;
			glutTimerFunc(1000,on_timer,countdown_timer);	
				
		}
	}
	return;
}





