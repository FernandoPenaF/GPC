#include "GL/glut.h"

void init(void) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(5,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(10,15,-1);
		glVertex3f(150,145,-1);
		glColor3f(0, 5, 0);
		glVertex3f(150, 15, -1);
		glVertex3f(10, 145, -1);
	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200,0);
	glutInitWindowSize(600,300);
	glutCreateWindow("Ejemplo");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}
	