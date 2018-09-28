#include "GL/glut.h"

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MATRIX_MODE);
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
	float xcenter = 140;
	float ycenter = 125;
	float zcenter = 0;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	angulo += 1.0f;
	glTranslatef(xcenter, ycenter, zcenter);
	glRotatef(angulo, 0.0, 0.0, 1.0);
	glTranslatef(-xcenter, -ycenter, -zcenter);
	
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
		glVertex3f(100, 100, 0);
		glVertex3f(100, 150, 0);
		glVertex3f(180, 150, 0);
		glVertex3f(180, 100, 0);
	glEnd();

	glPopMatrix();
	
	glBegin(GL_QUADS);
		glVertex3f(0, 50, 0);
		glVertex3f(50, 80, 0);
		glVertex3f(80, 50, 0);
		glVertex3f(80, 0, 0);
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
	angulo = 0.5;
	glutDisplayFunc(dibujar);
	glutIdleFunc(dibujar);
	//glutTimerFunc(0, timer, 0);
	glutMainLoop();
}