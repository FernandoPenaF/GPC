#include "GL/glut.h"

void init(void) {
	glClearColor(0.980, 0.922, 0.843,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void pinta(void) {
	double colorIncrement, colorCode;
	double incrementX, incrementX1, incrementY, incrementY1;
	double xOffset = 4.2, yOffset = 4.4;
	int xInit = 0, yInit = 0;
	int xLimit = 145, yLimit = 195;
	int increment = 5;
	int cont = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.45, 0.45, 0.85);
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
			xInit += 5;
			yInit += 5;
			xLimit -= 5;
			yLimit -= 5;
			cont++;
			glColor3f(0.55, 0.55, 0.85);
		}
	glEnd();

	colorCode = 0.55;
	colorIncrement = 0.045;
	glBegin(GL_TRIANGLES);
			for (int i = 0; i < 20; i++) {
				glColor3f(colorCode + i * colorIncrement, colorCode + i * (colorIncrement - 0.030), 0.85);
				glVertex3f(xInit + i * increment, (yLimit - yInit - 5 * increment) / 2, -1);
				glVertex3f(xLimit - xInit - 6 * increment, yLimit - yInit - 7 * increment, -1);
				glVertex3f(xLimit - xInit - 6 * increment, yInit, -1);
			}
			for (int i = 0; i < 20; i++) {
				glColor3f(colorCode + i * colorIncrement, colorCode + i * (colorIncrement - 0.030), 0.85);
				glVertex3f(xLimit - xInit - 4 * increment, yInit, -1);
				glVertex3f(xLimit - xInit - 4 * increment, yLimit - yInit - 7 * increment, -1);
				glVertex3f(xLimit + 11 * increment - i * increment, (yLimit - yInit - 5 * increment) / 2, -1);
			}
	glEnd();
	
	colorIncrement = 0.035;
	incrementY = 1.5;
	incrementY1 = 4.5;
	incrementX = 2.5;
	incrementX1 = 3.5;
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < 18; i++) {
			glColor3f(colorCode + i * colorIncrement, colorCode + i * colorIncrement, 0.85);
			glVertex3f(xInit + i * incrementX, (yLimit - yInit - 4.8 * increment + i * incrementY1) / 2, -1);
			glVertex3f(xLimit - xInit - 6.2 * increment - i * incrementX, yLimit - yInit - 7 * increment - yOffset / 8 - i * incrementY, -1);
			glVertex3f(xInit + i * incrementX, yLimit - yInit - 7 * increment - yOffset / 8 - i * incrementY, -1);
		}

		for (int i = 0; i < 15; i++) {
			glColor3f(colorCode + (i + .87) * colorIncrement, colorCode + (i + .87) * colorIncrement, 0.85);
			glVertex3f(xLimit - xInit - 3.8 * increment + i * incrementX1, yInit + (i * incrementY1)/2, -1);
			glVertex3f(xLimit + 10.9 * increment - i * incrementX, (yLimit - yInit - 5.4 * increment - i * incrementY1) / 2, -1);
			glVertex3f(xLimit + 10.9 * increment - i * incrementX, yInit + (i * incrementY1) / 2, -1);
		}
	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("Intento de cerámica");
	init();
	glutDisplayFunc(pinta);
	glutMainLoop();
}
	