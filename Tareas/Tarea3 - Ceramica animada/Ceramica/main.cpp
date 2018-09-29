#include "GL/glut.h"
#include "math.h"
#define M_PI 3.14159265358979323846

void init(void) {
	glClearColor(0.980, 0.922, 0.843,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

bool execute = true;
float color1 = 1.0f;
float color2 = 0.7f;
float color3 = 0.7f;
float colorIncrement, colorCode, anguloD, anguloI, anguloCD, anguloCI;
double incrementX, incrementX1, incrementY, incrementY1;
double xOffset, yOffset;
int xInit, yInit, xLimit, yLimit;
int increment, cont;

void timer(int value) {
	if (execute) {
		color1 += 0.001f;
		color2 += 0.002f;
	} else {
		color1 -= 0.001f;
		color2 -= 0.002f;
	}

	if (color2 > 0.85) //claros
		execute = false;
	else if (color2 < 0.35) //oscuros
		execute = true;

	glutPostRedisplay();
	glutTimerFunc(8, timer, 0);
}

void pintaMarcos(void) {
	xOffset = 4.2; yOffset = 4.4;
	xInit = 0; yInit = 0;
	xLimit = 145; yLimit = 195;
	increment = 5;
	cont = 0;

	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_QUADS);
		while (cont < 2) {
			for (int i = xInit; i < xLimit; i = i + increment) {
				glVertex3f(xInit, i, 0);
				glVertex3f(xInit, i + yOffset, 0);
				glVertex3f(xInit + xOffset, i + yOffset, 0);
				glVertex3f(xInit + xOffset, i, 0);
			}

			for (int i = yInit; i < yLimit; i = i + increment) {
				glVertex3f(i + xOffset, yInit, 0);
				glVertex3f(i + xOffset, yInit + yOffset, 0);
				glVertex3f(i, yInit + yOffset, 0);
				glVertex3f(i, yInit, 0);
			}

			for (int i = xInit; i < xLimit + increment; i = i + increment) {
				glVertex3f(yLimit, i, 0);
				glVertex3f(yLimit, i + yOffset, 0);
				glVertex3f(yLimit + xOffset, i + yOffset, 0);
				glVertex3f(yLimit + xOffset, i, 0);
			}

			for (int i = yInit; i < yLimit; i = i + increment) {
				glVertex3f(i + xOffset, xLimit, 0);
				glVertex3f(i + xOffset, xLimit + yOffset, 0);
				glVertex3f(i, xLimit + yOffset, 0);
				glVertex3f(i, xLimit, 0);
			}
			xInit += 5;
			yInit += 5;
			xLimit -= 5;
			yLimit -= 5;
			cont++;
			glColor3f(1.0, 0.7, 0.7);
		}
	glEnd();
}

void pintaInternosD(void) {
	colorCode = 0.55;
	colorIncrement = 0.045;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++) {
		glColor3f(color1 + i * colorIncrement, color2 + i * (colorIncrement - 0.030), color3);
		//glColor3f(colorCode + i * colorIncrement, colorCode + i * (colorIncrement - 0.030), 0.85);
		glVertex3f(xInit + i * increment, (yLimit - yInit - 5 * increment) / 2, 0);
		glVertex3f(xLimit - xInit - 6 * increment, yLimit - yInit - 7 * increment, 0);
		glVertex3f(xLimit - xInit - 6 * increment, yInit, 0);
	}
	glEnd();
}

void pintaInternosI(void) {
	colorCode = 0.55;
	colorIncrement = 0.045;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++) {
		glColor3f(color1 + i * colorIncrement, color2 + i * (colorIncrement - 0.030), color3);
		//glColor3f(colorCode + i * colorIncrement, colorCode + i * (colorIncrement - 0.030), 0.85);
		glVertex3f(xLimit - xInit - 4 * increment, yInit, 0);
		glVertex3f(xLimit - xInit - 4 * increment, yLimit - yInit - 7 * increment, 0);
		glVertex3f(xLimit + 11 * increment - i * increment, (yLimit - yInit - 5 * increment) / 2, 0);
	}
	glEnd();
}

void pintaExtremos(void) {
	colorIncrement = 0.035;
	incrementY = 1.5;
	incrementY1 = 4.5;
	incrementX = 2.5;
	incrementX1 = 3.5;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 18; i++) {
		glColor3f(color1 + i * colorIncrement, color2 + i * colorIncrement, color3);
		//glColor3f(colorCode + i * colorIncrement, colorCode + i * colorIncrement, 0.85);
		glVertex3f(xInit + i * incrementX, (yLimit - yInit - 4.8 * increment + i * incrementY1) / 2, 0);
		glVertex3f(xLimit - xInit - 6.2 * increment - i * incrementX, yLimit - yInit - 7 * increment - yOffset / 8 - i * incrementY, 0);
		glVertex3f(xInit + i * incrementX, yLimit - yInit - 7 * increment - yOffset / 8 - i * incrementY, 0);
	}

	for (int i = 0; i < 15; i++) {
		glColor3f(color1 + (i + .87) * colorIncrement, color2 + (i + .87) * colorIncrement, color3);
		//glColor3f(colorCode + (i + .87) * colorIncrement, colorCode + (i + .87) * colorIncrement, 0.85);
		glVertex3f(xLimit - xInit - 3.8 * increment + i * incrementX1, yInit + (i * incrementY1) / 2, 0);
		glVertex3f(xLimit + 10.9 * increment - i * incrementX, (yLimit - yInit - 5.4 * increment - i * incrementY1) / 2, 0);
		glVertex3f(xLimit + 10.9 * increment - i * incrementX, yInit + (i * incrementY1) / 2, 0);
	}
	glEnd();
}

void pintaCirculo(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 1000;
	GLfloat twicePi = 2.0f * M_PI;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(5.0);

	glBegin(GL_LINES);
	glColor3f(color1, color2, color3);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(x, y);
		glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}

int it = 1000;

void pinta(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLfloat xcenter = 100;
	GLfloat ycenter = 75;
	
	pintaMarcos();
	pintaExtremos();

	glPushMatrix();
		anguloCD -= 0.5f;
		glTranslatef(xcenter, ycenter, 0);
		glRotatef(anguloCD, 0.0, 0.0, 1.0);
		glScalef(0.5f, 0.5f, 0);
		glTranslatef(-xcenter, -ycenter, 0);
		pintaCirculo(30, 30, 20);
	glPopMatrix();

	glPushMatrix();
		anguloCD -= 0.5f;
		glTranslatef(xcenter, ycenter, 0);
		glRotatef(anguloCD, 0.0, 0.0, 1.0);
		glScalef(0.5f, 0.5f, 0);
		glTranslatef(-xcenter, -ycenter, 0);
		pintaCirculo(170, 120, 20);
	glPopMatrix();

	glPushMatrix();
		anguloCD -= 0.5f;
		glTranslatef(xcenter, ycenter, 0);
		glRotatef(anguloCD, 0.0, 0.0, 1.0);
		glScalef(0.5f, 0.5f, 0);
		glTranslatef(-xcenter, -ycenter, 0);
		pintaCirculo(170, 120, 20);
	glPopMatrix();

	if (it <= 0) {
		glPushMatrix();
			anguloD -= 0.5f;
			glTranslatef(xcenter, ycenter, 0);
			glRotatef(anguloD, 0.0, 0.0, 1.0);
			glScalef(0.5f, 0.5f, 0);
			glTranslatef(-xcenter, -ycenter, 0);
			pintaInternosD();
		glPopMatrix();
	}
	else {
		glPushMatrix();
			glTranslatef(xcenter, ycenter, 0);
			glScalef(0.5f, 0.5f, 0);
			glTranslatef(-xcenter, -ycenter, 0);
			pintaInternosD();
		glPopMatrix();
		--it;
	}

	if (it <= 0) {
		glPushMatrix();
			anguloI += 0.5f;
			glTranslatef(xcenter, ycenter, 0);
			glRotatef(anguloI, 0.0, 0.0, 1.0);
			glScalef(0.5f, 0.5f, 0);
			glTranslatef(-xcenter, -ycenter, 0);
			pintaInternosI();
		glPopMatrix();
	}
	else {
		glPushMatrix();
			glTranslatef(xcenter, ycenter, 0);
			glScalef(0.5f, 0.5f, 0);
			glTranslatef(-xcenter, -ycenter, 0);
			pintaInternosI();
		glPopMatrix();
	}

	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("Intento de cerámica 2.0");
	init();
	anguloD = 0.0, anguloI = 0.0, anguloCD = 0.0, anguloCI = 0.0;
	glutDisplayFunc(pinta);
	//glutIdleFunc(pinta);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
}
	