#include <gl/glut.h>
#include <stdio.h>

GLfloat aspecto, angulo, rot1 = 40, rot2 = 0, rot3 = 20;

void desenhaObjetos(void){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glPushMatrix();
       glRotatef(rot1, 0,1,0);
        glTranslatef(1,-20,50);

        //cabeca//
        glPushMatrix();
            glTranslated(-20, 13, 0);
            glScalef(1.5, 1, 1.8);
            glColor3f(1, 0.71, 0.76);
            glutSolidCube(3);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-20, 15, -4);
            glColor3f(0, 0, 0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-20, 15, 4);
            glColor3f(0, 0, 0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-20, 15, -3);
            glColor3f(1, 1, 1);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-20, 15, 3);
            glColor3f(1, 1, 1);
            glutSolidCube(1);
        glPopMatrix();

    //corpo do porco//
     glPushMatrix();
        glColor3f(1, 0.71, 0.76);
        glScalef(3, 1.5, 1.8);
        glTranslatef(0, 7, 0);
        glutSolidCube(8);
    glPopMatrix();
     glPushMatrix();
         glColor3f(1, 0.71, 0.76);
        glTranslatef(-15, 14, 0);
        glutSolidCube(10);
     glPopMatrix();

     //pernas do porco//
     glPushMatrix();
      glRotatef(90, 0, 1, 0);
       glColor3f(1, 0.71, 0.76);
     glPushMatrix();
        glScalef(1, 2.2, 1);
        glTranslatef(-4.6, 1, 9);
        glRotatef(rot2, 1, 0, 0);
        glutSolidCube(5);
    glPopMatrix();
    glPushMatrix();
        glScalef(1, 2.2, 1);
        glTranslatef(4.6, 1, 9);
        glRotatef(rot3, 1, 0, 0);
        glutSolidCube(5);
    glPopMatrix();
    glPushMatrix();
        glScalef(1, 2.2, 1);
        glTranslatef(-4.6, 1, -9);
        glRotatef(rot2, 1, 0, 0);
        glutSolidCube(5);
    glPopMatrix();
    glPushMatrix();
        glScalef(1, 2.2, 1);
        glTranslatef(4.6, 1, -9);
        glRotatef(rot3, 1, 0, 0);
        glutSolidCube(5);
    glPopMatrix();
    glPopMatrix();
glPopMatrix();
glutSwapBuffers();
}

//timer para movimentacao das pernas//
void timerPernas(int passo){
    if(rot2 == 0){
        rot2 = 20;
    }else
     if(rot2 == 20){
        rot2 = 0;
    }
    if(rot3 == 0){
        rot3 = 20;

    }else
     if(rot3 == 20){
        rot3 = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(800,timerPernas,1);
}

void Inicializa (void){
    GLfloat luzAmbiente[4]={0.3,0.3,0.3,1.0};
	GLfloat luzDifusa[4]={1.0, 1.0, 1.0,1.0};	        // "cor"
	GLfloat luzEspecular[4]={0.8, 0.6, 0.6, 1.0};   // "brilho"
	GLfloat posicaoLuz[4]={1000.0, 1000.0, 15.0, 1.0};

	//Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

    glClearColor(0.13,0.55,0.13,1);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

    angulo = 40;

printf("Use as setas do teclado para mover o porco");
}

void projetaPlano(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angulo, aspecto, 0.4, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){
    if ( h == 0 ) h = 1;
    glViewport(0, 0, w, h);
    aspecto = (GLfloat)w/(GLfloat)h;
    projetaPlano();
}

//movimentar porco//
void teclasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){
        case GLUT_KEY_LEFT:
            rot1 = ((int) rot1  - 1);
        break;
        case GLUT_KEY_RIGHT:
            rot1 = ((int) rot1 + 1);
        break;
    }
    glutPostRedisplay();
}

int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(300,120);
     glutCreateWindow("Atividade OpenGL 3D");
     glutDisplayFunc(desenhaObjetos);
      glutTimerFunc(10,timerPernas,1);
     glutSpecialFunc(teclasDirecionais);
     glutReshapeFunc(AlteraTamanhoJanela);
     Inicializa();
     glutMainLoop();
     return 0;
}
