#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

float transparency = 1.0;
float angle = 0.0, zCube = -5.0, zSphere = -10.0;
float sX = 1.0, sY = 1.0, sZ = 1.0;
bool rotate = false, ida = true, move = false;
int windowID;

GLfloat colorCube[] = {0.5, 0.5, 0.5, 1.0};
GLfloat colorSphere[] = { 0.5, 0.5, 0.5, 1.0 };

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

	glPushMatrix();
		glTranslatef(-1.0, 0.0, zCube);
		glScalef(sX, sY, sZ);
		if (rotate) {
			glRotatef(angle, 1.0, 0.0, 0.0);
			glRotatef(angle, 1.0, 0.0, 1.0);
		}
		glColor4f(colorCube[0], colorCube[1], colorCube[2], colorCube[3]);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0, 0.0, zSphere);
		glScalef(sX, sY, sZ);
		if (rotate) {
			glRotatef(angle, 1.0, 1.0, 0.0);
			glRotatef(angle, 1.0, 0.0, 0.0);
		}
		glColor4f(colorSphere[0], colorSphere[1], colorSphere[2], colorSphere[3]);
		glutSolidSphere(0.5, 8, 6);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

// Initializes 3D rendering
void initRendering() {
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

	if (move) {
		if (zCube <= -15) {
			ida = false;
		} else if (zCube >= -5) {
			ida = true;
		}

		if (ida) {
			zCube -= 0.1f;
			zSphere += 0.1f;
		} else {
			zCube += 0.1f;
			zSphere -= 0.1f;
		}
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
	case 'M':
		move = !move;
		break;
	case 'E':
		sX = 1.5;
		sY = 1.5;
		sZ = 1.0;
		break;
	case 'e':
		sX = 1.0;
		sY = 1.0;
		sZ = 1.0;
		break;
	case 'R':
		rotate = !rotate;
		break;
	case 'C':
		for (int i = 0; i < 3; i++){
			colorCube[i] = (float) rand() / (float) RAND_MAX;
			colorSphere[i] = (float) rand() / (float) RAND_MAX;
		}
		//printf("R: %f, G: %f, B: %f\n", colorCube[0], colorCube[1], colorCube[2]);
		//printf("R: %f, G: %f, B: %f\n", colorSphere[0], colorSphere[1], colorSphere[2]);
		break;
	case 'T':
		scanf("%f", &transparency);
		colorCube[3] = transparency;
		colorSphere[3] = (float)rand() / (float)RAND_MAX;
		//printf("Transparency: %f\n", colorCube[3]);
		//printf("Transparency: %f\n", colorSphere[3]);
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
	srand(static_cast <unsigned> (time(0)));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1100, 900);
	glutInitWindowPosition(0, 0);
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