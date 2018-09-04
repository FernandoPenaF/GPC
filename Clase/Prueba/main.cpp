#include "GL/glut.h"

void init(void) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void cuadrado(void) {
	double xOffset = 4.2;
	double yOffset = 4.4;
	int xInit = 5;
	int yInit = 5;
	int xLimit = 145;
	int yLimit = 190;
	int cont = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_QUADS);
	while (cont < 2) {
		for (int i = xInit; i < xLimit; i = i + 5) {
			glVertex3f(xInit, i, -1);
			glVertex3f(xInit, i + yOffset, -1);
			glVertex3f(xInit + xOffset, i + yOffset, -1);
			glVertex3f(xInit + xOffset, i, -1);
		}

		for (int i = yInit; i < yLimit; i = i + 5) {
			glVertex3f(i + xOffset, yInit, -1);
			glVertex3f(i + xOffset, yInit + yOffset, -1);
			glVertex3f(i, yInit + yOffset, -1);
			glVertex3f(i, yInit, -1);
		}

		for (int i = xInit; i < xLimit + 5; i = i + 5) {
			glVertex3f(yLimit, i, -1);
			glVertex3f(yLimit, i + yOffset, -1);
			glVertex3f(yLimit + xOffset, i + yOffset, -1);
			glVertex3f(yLimit + xOffset, i, -1);
		}

		for (int i = yInit; i < yLimit; i = i + 5) {
			glVertex3f(i + xOffset, xLimit, -1);
			glVertex3f(i + xOffset, xLimit + yOffset, -1);
			glVertex3f(i, xLimit + yOffset, -1);
			glVertex3f(i, xLimit, -1);
		}
		xInit -= 5;
		yInit -= 5;
		xLimit -= 5;
		yLimit -= 5;
		cont++;
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
	glutInitWindowSize(600,600);
	glutCreateWindow("Ejemplo");
	init();
	glutDisplayFunc(cuadrado);
	glutMainLoop();
}
	