#include "GL/glut.h"

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}

float angulo;

float color1 = 0.0f;
float color2 = 0.0f;
float color3 = 0.0f;
void timer(int value){

	//changeColor?
	color1 += 0.001f;
	color2 += 0.003f;
	color3 += color2;
	if (color1 > 1.0)
		color1 = 0;
	if (color2 > 1.0)
		color2 = 0;
	if (color3 > 1.0)
		color3 = 0;

	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}


void dibujar() {

	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(angulo, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	//glColor3f(1.0, 0.0, 0.0);
	glColor3f(color1, color2, color3);
	glVertex3f(100, 100, 0);
	glVertex3f(160, 160, 0);
	glVertex3f(160, 100, 0);
	glEnd();
	glutSwapBuffers();
}


void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Ejemplo");
	init();
	angulo = 0.07;
	glutDisplayFunc(dibujar);
	glutIdleFunc(dibujar);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
}