#include "GL/glut.h"
#include "math.h"
# define M_PI 3.14159265358979323846

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MATRIX_MODE);
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}

float angulo;

void drawCircle(GLfloat x, GLfloat y, GLfloat radius)
{
	int i;
	int triangleAmount = 1000;
	GLfloat twicePi = 2.0f * M_PI;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(5.0);

	glBegin(GL_LINES);
		glColor4f(1.0, 0.0, 0.0, 1.0);
		for (i = 0; i <= triangleAmount; i++){
			glVertex2f(x, y);
			glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
		}
	glEnd();
}

void dibujar() {
	drawCircle(100, 100, 50);
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
	glutMainLoop();
}