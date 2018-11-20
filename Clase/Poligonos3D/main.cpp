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
	bool ida;
	GLfloat color[4];
};

int i = 0;
float transparency = 1.0, scale = 1.0;
float scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;
float angle = 0.0, zSphere = -10.0;
bool rotate = false, move = false;
int windowID;

std::vector<cube> cubes;

GLfloat colorSphere[] = { 0.5, 0.5, 0.5, 1.0 };

cube generateCube(int l, float x, float y, float z, float r, float g, float b, float t) {
	cube cube1;
	cube1.len = l;
	cube1.posX = x;
	cube1.posY = y;
	cube1.posZ = z;
	cube1.color[0] = r;
	cube1.color[1] = g;
	cube1.color[2] = b;
	cube1.color[3] = t;
	return cube1;
}

void addCube(int l, float x, float y, float z, float r, float g, float b, float t) {
	cubes.push_back(generateCube(l, x, y, z, r, g, b, t));
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
			glScalef(scaleX, scaleY, scaleZ);
			if (rotate) {
				glRotatef(angle, 1.0, 0.0, 0.0);
				glRotatef(angle, 1.0, 0.0, 1.0);
			}
			glColor4f(c.color[0], c.color[1], c.color[2], c.color[3]);
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
		for (int i = 0; i < cubes.size(); i++) {
			float z = cubes[i].posZ;

			if (z <= -15) {
				cubes[i].ida = false;
			} else if (z >= -5 ) {
				cubes[i].ida = true;
			}

			if (cubes[i].ida) {
				cubes[i].posZ -= 0.1f;
			} else {
				cubes[i].posZ += 0.1f;
			}
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
		float x, y, z, r, g, b;
		x = randomFloat(-2.5, 2.5);
		y = randomFloat(-1.5, 1.5);
		z = randomFloat(-10.0, -3.0);
		r = randomFloat(0, 1);
		g = randomFloat(0, 1);
		b = randomFloat(0, 1);
		addCube(1, x, y, z, r, g, b, transparency);
		break;
	case 'M':
		move = !move;
		break;
	case 'E':
		scanf("%f", &scale);
		scaleX = scale;
		scaleY = scale;
		scaleZ = scale;
		break;
	case 'e':
		scaleX = 1.0;
		scaleY = 1.0;
		scaleZ = 1.0;
		break;
	case 'R':
		rotate = !rotate;
		break;
	case 'C':
		for (int i = 0; i < cubes.size(); i++){
			cubes[i].color[0] = randomFloat(0, 1);
			cubes[i].color[1] = randomFloat(0, 1);
			cubes[i].color[2] = randomFloat(0, 1);
		}
		break;
	case 'T':
		scanf("%f", &transparency);
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].color[3] = transparency;
		}
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