#include "GL/glut.h"

void init(void) {
	glClearColor(0.980, 0.922, 0.843,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void cuadrado(void) {
	double colorIncrement, colorCode;
	double xOffset = 4.2;
	double yOffset = 4.4;
	int increment = 5;
	int xInit = 0;
	int yInit = 0;
	int xLimit = 145;
	int yLimit = 195;
	int tempXInit, tempYInit, tempXLimit, tempYLimit;
	int cont = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25, 0.25, 0.25);

	glBegin(GL_QUADS);
		while (cont < 2) {
			for (int i = xInit; i < xLimit; i = i + increment) {
				glVertex3f(xInit, i, -1);
				glVertex3f(xInit, i + yOffset, -1);
				glVertex3f(xInit + xOffset, i + yOffset, -1);
				glVertex3f(xInit + xOffset, i, -1);
			}

			for (int i = yInit; i < yLimit; i = i + increment) {
				glVertex3f(i + xOffset, yInit, -1);
				glVertex3f(i + xOffset, yInit + yOffset, -1);
				glVertex3f(i, yInit + yOffset, -1);
				glVertex3f(i, yInit, -1);
			}

			for (int i = xInit; i < xLimit + increment; i = i + increment) {
				glVertex3f(yLimit, i, -1);
				glVertex3f(yLimit, i + yOffset, -1);
				glVertex3f(yLimit + xOffset, i + yOffset, -1);
				glVertex3f(yLimit + xOffset, i, -1);
			}

			for (int i = yInit; i < yLimit; i = i + increment) {
				glVertex3f(i + xOffset, xLimit, -1);
				glVertex3f(i + xOffset, xLimit + yOffset, -1);
				glVertex3f(i, xLimit + yOffset, -1);
				glVertex3f(i, xLimit, -1);
			}

			glColor3f(0.35, 0.35, 0.35);
			xInit += 5;
			yInit += 5;
			xLimit -= 5;
			yLimit -= 5;
			cont++;
		}
	glEnd();
	
	tempXInit = xInit;
	tempYInit = yInit;
	tempXLimit = xLimit;
	tempYLimit = yLimit;

	glBegin(GL_TRIANGLES);
		colorIncrement = 0.045;
		colorCode = 0.35;
			for (int i = 0; i < 20; i++) {
				glColor3f(colorCode + i * colorIncrement, colorCode + i * colorIncrement, colorCode + i * colorIncrement);
				glVertex3f(xInit + i * increment, (yLimit - yInit - 5 * increment) / 2, -1);
				glVertex3f(xLimit - xInit - 6 * increment, yLimit - yInit - 7 * increment, -1);
				glVertex3f(xLimit - xInit - 6 * increment, yInit, -1);
			}

			for (int i = 0; i < 20; i++) {
				glColor3f(colorCode + i * colorIncrement, colorCode + i * colorIncrement, colorCode + i * colorIncrement);
				glVertex3f(xLimit - xInit - 4 * increment, yInit, -1);
				glVertex3f(xLimit - xInit - 4 * increment, yLimit - yInit - 7 * increment, -1);
				glVertex3f(xLimit + 11 * increment - i * increment, (yLimit - yInit - 5 * increment) / 2, -1);
			}
	glEnd();
	
	xInit = tempXInit;
	yInit = tempYInit;
	xLimit = tempXLimit;
	yLimit = tempYLimit;

	glColor3f(0, 1.0, 0);
	glBegin(GL_TRIANGLES);
		glVertex3f(xInit, (yLimit - yInit - 4.8 * increment) / 2, -1);
		glVertex3f(xLimit - xInit - 6.2 * increment, yLimit - yInit - 7 * increment - yOffset / 8, -1);
		glVertex3f(xInit, yLimit - yInit - 7 * increment - yOffset / 8, -1);

		glVertex3f(xLimit - xInit - 3.8 * increment, yInit, -1);
		glVertex3f(xLimit + 10.9 * increment, (yLimit - yInit - 5.4 * increment) / 2, -1);
		glVertex3f(xLimit + 10.9 * increment, yInit, -1);
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
	