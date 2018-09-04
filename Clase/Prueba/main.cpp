#include "GL/glut.h"

void init(void) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void cuadrado(void) {
	int offset = 4;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
		for (int i = 10; i < 140; i = i + 5) {
			glVertex3f(10, i, -1);
			glVertex3f(10, i + offset, -1);
			glVertex3f(15, i + offset, -1);
			glVertex3f(15, i, -1);
		}
		
	glEnd();
	glFlush();
}

void cuadrados(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(5, 0, 0);
	glBegin(GL_QUADS);
	for (int i = 0; i < 250; i = i + 25) {
		glVertex3f(0, 0, -1);
		glVertex3f(0, 10, -1);
		glVertex3f(10, 10, -1);
		glVertex3f(10, 0, -1);
	}
	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200,0);
	glutInitWindowSize(750,600);
	glutCreateWindow("Ejemplo");
	init();
	glutDisplayFunc(cuadrado);
	glutMainLoop();
}
	