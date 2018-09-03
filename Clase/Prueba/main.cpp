#include "GL/glut.h"

void init(void) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void cuadrado(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(5,0,0);
	glBegin(GL_QUADS);
		glVertex3f(10, 10, -1);
		glVertex3f(10, 20, -1);
		glVertex3f(20, 20, -1);
		glVertex3f(20, 10, -1);

		glVertex3f(25, 10, -1);
		glVertex3f(25, 20, -1);
		glVertex3f(35, 20, -1);
		glVertex3f(35, 10, -1);
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
	glutInitWindowSize(450,400);
	glutCreateWindow("Ejemplo");
	init();
	glutDisplayFunc(cuadrado);
	glutMainLoop();
}
	