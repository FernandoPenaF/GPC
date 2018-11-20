#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

struct cube {
	int len;
	float posX;
	float posY;
	float posZ;
};

int i = 0;
float transparency = 1.0;
float angle = 0.0, zCube = -5.0, zSphere = -10.0;
float sX = 1.0, sY = 1.0, sZ = 1.0;
bool rotate = false, ida = true, move = false;
int windowID;

std::vector<cube> cubes;

GLfloat colorCube[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat colorSphere[] = { 0.5, 0.5, 0.5, 1.0 };

cube generateCube(int l, float x, float y, float z) {
	cube cube1;
	cube1.len = l;
	cube1.posX = x;
	cube1.posY = y;
	cube1.posZ = z;
	return cube1;
}

void addCube(int l, float x, float y, float z) {
	cubes.push_back(generateCube(l, x, y, z));
}

void drawCube() {
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

	for (i = 0; i < cubes.size(); i++) {
		cube c = cubes[i];
		
		glPushMatrix();
			glTranslatef(c.posX, c.posY, c.posZ);
			glScalef(sX, sY, sZ);
			if (rotate) {
				glRotatef(angle, 1.0, 0.0, 0.0);
				glRotatef(angle, 1.0, 0.0, 1.0);
			}
			glColor4f(colorCube[1], colorCube[1], colorCube[2], colorCube[3]);
			glutSolidCube(c.len);
		glPopMatrix();
	}

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
		zCube = cubes[0].posZ;
		if (zCube <= -15) {
			ida = false;
		} else if (zCube >= -5) {
			ida = true;
		}

		if (ida) {
			cubes[0].posZ -= 0.1f;
			cubes[1].posZ += 0.1f;
		} else {
			cubes[0].posZ += 0.1f;
			cubes[1].posZ -= 0.1f;
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

float randomFloat(float min, float max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

void keyboardCB(unsigned char key, int x, int y){
	switch (key){
	case 'A':
		float x;
		x = randomFloat(-2.0, 2.0);
		printf("R: %f\n", x);
		addCube(1, x, 0.0, -6);
		break;
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
		colorCube[0] = (float)rand() / (float)RAND_MAX;
		colorCube[1] = (float)rand() / (float)RAND_MAX;
		colorCube[2] = (float)rand() / (float)RAND_MAX;
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

	addCube(1, -1.0, 0.0, -5.0);
	addCube(1, 1.0, 0.0, -10.0);

	glutDisplayFunc(drawCube);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutKeyboardFunc(keyboardCB);
	glutMainLoop();
	return 0;
}