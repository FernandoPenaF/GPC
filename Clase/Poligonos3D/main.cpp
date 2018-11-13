#include <GL/glut.h>
#include <iostream>

float angle = 0.0;
float sX = 1.0, sY = 1.0, sZ = 1.0;
bool rotate = false;
int windowID;

void drawCube(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -5.0);
	if(rotate)
		glRotatef(angle, 1.0, 0.0, 0.0);
	//glRotatef(angle, 1.0, 1.0, 0.0);
	//glRotatef(angle, 0.0, 0.0, 1.0);

	glScalef(sX, sY, sZ);
	//glutWireCube(1.0);

	glutWireSphere(0.75, 8, 6);
	//glutWireCone(0.7, 2.0, 7, 6);

	glFlush();
	glutSwapBuffers();
}

// Function for increasing the angle variable smoothly, 
// keeps it <=360
// It can also be implemented using the modulo operator.
void update(int value) {
	angle += 1.0f;
	if (angle > 360) {
		angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

// Called when the window is resized
void handleResize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void keyboardCB(unsigned char key, int x, int y){
	switch (key){
	case 'E':
		sX = 2.0;
		sY = 2.0;
		sZ = 1.0;
		break;
	case 'e':
		sX = 1.0;
		sY = 1.0;
		sZ = 1.0;
		break;
	case 'M':
		rotate = true;
		break;
	case 'm':
		rotate = false;
		break;
	case 27: // Escape key
		glutDestroyWindow(windowID);
		exit(0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	windowID = glutCreateWindow("OpenGL - Rotating a Sphere");

	glutDisplayFunc(drawCube);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);
	glutKeyboardFunc(keyboardCB);
	glutMainLoop();
	return 0;
}