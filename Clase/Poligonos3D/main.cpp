#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

float angle = 0.0;
float colorR = 0.3, colorG = 0.3, colorB = 0.3, transparency = 1.0;
float sX = 1.0, sY = 1.0, sZ = 1.0;
bool rotate = false, seed = false;
int windowID;

void drawCube(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Add an ambient light
	GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// Add a positioned light
	GLfloat lightColor0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightPos0[] = { 4.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glTranslatef(0.0, 0.0, -5.0);
	glColor4f(colorR, colorG, colorB, transparency);
	glScalef(sX, sY, sZ);
	if (rotate) {
		glRotatef(angle, 1.0, 0.0, 0.0);
		glRotatef(angle, 1.0, 0.0, 1.0);
	}
	
	glutSolidCube(1);
	//glutSolidSphere(0.75, 8, 6);
	glFlush();
	glutSwapBuffers();
}

// Initializes 3D rendering
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	// Set the color of the background
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
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
	case 'C':
		srand(static_cast <unsigned> (time(0)));
		colorR = (float) rand() / (float) RAND_MAX;
		colorG = (float) rand() / (float) RAND_MAX;
		colorB = (float) rand() / (float) RAND_MAX;
		break;
	case 'T':
		//scanf("%f", &transparency);
		transparency = (float) rand() / (float) RAND_MAX;
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
	initRendering();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(drawCube);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutKeyboardFunc(keyboardCB);
	glutMainLoop();
	return 0;
}