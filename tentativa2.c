

// Usar o comando gcc tentativa2.c  -lGL -lGLU -lglut -lm no Linux
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


GLsizei winWidth = 800, winHeight = 800;

//Inicializa as definicões do OpenGL
void init(void)
{
	glClearColor (0.0, 0.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, winWidth, 0.0, winHeight);
    glShadeModel (GL_SMOOTH);
}



//Desenha o Triangulo
void drawTriangle()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glBegin( GL_TRIANGLES);
    glColor3f(30.0, 50.0, 10.0);  
    glVertex2i(50, 50);
    glVertex2i(100, 50);
    glVertex2i(50,40);

    glVertex2i(75, 100);
    glVertex2i(120,40);
    glVertex2i(40,20);
   glEnd();

}


//Desenha o quadrado
void drawSquare()
{
  glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);  
    glVertex2i(100 , 100);
    glVertex2i(0, 100);
    glVertex2i(0, 0);
    glFlush();
   glEnd();

}







//Função de criar as formas
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);	
   drawSquare();
   drawTriangle();
  
  glFlush();  
}



int main (int argc, char** argv)
{
	glutInit (&argc, argv);							
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (400, 400);				
	glutInitWindowSize (winWidth, winHeight);		
	glutCreateWindow ("Trabalho 1");
	
	init();							
	glutDisplayFunc (display);				
	glutMainLoop ( );				 
}