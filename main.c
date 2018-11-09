#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>


#define MAP_SIZE 10
#define UNUSED(x) ((void)x)
/* Dimenzije prozora */
static int window_width, window_height;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

static float px = 2;
//static float py = 0;
static float pz = 2;
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

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
    

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
    case 'd':
        px -=1;
	    on_display();
	    break;
    case 'a':
	    px+=1;
	    on_display();
	    break;
    case 'w':
	    pz+=1;
	    on_display();
    	break;
    case 's':
	    pz-=1;
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
            0.05, 25);

   
    /* Podesava se tacka pogleda koja zavisi od pozicije igraca*/
        
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
    	gluLookAt(px+0.5,0.9,pz+0.6,
            px+0.5,1,pz+MAP_SIZE,
            0,1,0
        );

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

    
    //mapa iscrtavanje
    
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(0,0,0);
        glVertex3f(0,0,MAP_SIZE);
        glVertex3f(MAP_SIZE,0,MAP_SIZE);
        glVertex3f(MAP_SIZE,0,0);
    glEnd();
    int i;
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
    
    /*Iscrtavanje karaktera*/
    drawPlayer(px,pz);
    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

void drawPlayer(int x,int y){
    
    int px = x;
    int py = y;

    /*leva i desna noga*/
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
    
    //telo
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(px+0.5, 0.6, py+0.5);
    glScalef(3,2,3);
    glutSolidCube(0.2);
    glPopMatrix();
    
    //glava
    glPushMatrix();
    glColor3f(0.5, 0.5, 1);
    glTranslatef(px+0.5, 0.9, py+0.5);
    glScalef(1,1,1);
    glutSolidCube(0.2);
    glPopMatrix();
    
    //leva i desna ruka
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



