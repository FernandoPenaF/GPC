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

struct sphere {
	double radius;
	int slices;
	int stacks;
	float posX;
	float posY;
	float posZ;
	bool ida;
	GLfloat color[4];
};

float x, y, z, r, g, b;
float cubeTransparency = 1.0, sphereTransparency = 1.0, ellipseTransparency = 1.0, cubeScale, sphereScale, ellipseScale;
float scaleCube[3], scaleSphere[3], scaleEllipse[3];
float cubeAngle = 0.0, ellipseAngle = 0.0, menuAngle = 0.0;
bool cubeRotate = false, cubeMove = false, sphereMove = false, ellipseRotate = false, ellipseMove = false;
int windowID;

std::vector<cube> cubes;
std::vector<sphere> spheres;
std::vector<sphere> ellipses;
std::vector<cube> bars;

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

sphere generateSphere(double rad, int sl, int stk, float x, float y, float z, float r, float g, float b, float t) {
	sphere sphere1;
	sphere1.radius = rad;
	sphere1.slices = sl;
	sphere1.stacks = stk;
	sphere1.posX = x;
	sphere1.posY = y;
	sphere1.posZ = z;
	sphere1.color[0] = r;
	sphere1.color[1] = g;
	sphere1.color[2] = b;
	sphere1.color[3] = t;
	return sphere1;
}

sphere generateEllipse(double rad, int sl, int stk, float x, float y, float z, float r, float g, float b, float t) {
	sphere ellipse1;
	ellipse1.radius = rad;
	ellipse1.slices = sl;
	ellipse1.stacks = stk;
	ellipse1.posX = x;
	ellipse1.posY = y;
	ellipse1.posZ = z;
	ellipse1.color[0] = r;
	ellipse1.color[1] = g;
	ellipse1.color[2] = b;
	ellipse1.color[3] = t;
	return ellipse1;
}

void addCube(int l, float x, float y, float z, float r, float g, float b, float t) {
	cubes.push_back(generateCube(l, x, y, z, r, g, b, t));
}

void addSphere(double rad, int sl, int stk, float x, float y, float z, float r, float g, float b, float t) {
	spheres.push_back(generateSphere(rad, sl, stk, x, y, z, r, g, b, t));
}

void addEllipse(double rad, int sl, int stk, float x, float y, float z, float r, float g, float b, float t) {
	ellipses.push_back(generateEllipse(rad, sl, stk, x, y, z, r, g, b, t));
}


void polygons() {
	glPushMatrix();
	glRotatef(0.5, 1, 1, 0);
	
	glPopMatrix();
}


void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Add an ambient light
	GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// Add a positioned light
	GLfloat lightColor0[] = { 1.0,1.0, 1.0, 1.0 };
	GLfloat lightPos0[] = { 0.0, 0.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);



	//------------------------------------------------------------------------------------------------------------------
	glViewport(390, 220, 1200, 675);
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	for (int i = 0; i < cubes.size(); i++) {
		cube c = cubes[i];
		
		glPushMatrix();
			glTranslatef(c.posX, c.posY, c.posZ);
			glScalef(scaleCube[0], scaleCube[1], scaleCube[2]);
			if (cubeRotate) {
				glRotatef(cubeAngle, 1.0, 0.0, 0.0);
				glRotatef(cubeAngle, 1.0, 0.0, 1.0);
			}
			glColor4f(c.color[0], c.color[1], c.color[2], c.color[3]);
			glutSolidCube(c.len);
		glPopMatrix();
	}

	for (int i = 0; i < spheres.size(); i++) {
		sphere sp = spheres[i];

		glPushMatrix();
			glTranslatef(sp.posX, sp.posY, sp.posZ);
			glScalef(scaleSphere[0], scaleSphere[1], scaleSphere[2]);
			//glRotatef(ellipseAngle, 1.0, 1.0, 1.0); //Optional
			glColor4f(sp.color[0], sp.color[1], sp.color[2], sp.color[3]);
			glutSolidSphere(sp.radius, sp.slices, sp.stacks);
		glPopMatrix();
	}

	for (int i = 0; i < ellipses.size(); i++) {
		sphere elip = ellipses[i];

		glPushMatrix();
			glTranslatef(elip.posX, elip.posY, elip.posZ);
			glScalef(scaleEllipse[0], scaleEllipse[1], scaleEllipse[2]);
			if (ellipseRotate) {
				glRotatef(cubeAngle, 1.0, 0.0, 0.0);
				glRotatef(ellipseAngle, 1.0, 0.0, 1.0);
			}
			glColor4f(elip.color[0], elip.color[1], elip.color[2], elip.color[3]);
			glutSolidSphere(elip.radius, elip.slices, elip.stacks);
		glPopMatrix();
	}

	for (int i = -22; i <= 22; i = i + 2) {
		glPushMatrix();
			glTranslatef(i, 0.0, -30.0);
			glScalef(1.0, 26.0, 1.0);
			glColor4f(0.2, 0.2, 0.2, 1.0);
			glutSolidCube(1);
		glPopMatrix();
	}

	
	//------------------------------------------------------------------------------------------------------------------
	//viewport donde se van a poner las figuras que van a funcionar como boton
	glViewport(10,220, 350, 675);
	//gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glLoadIdentity();
	
	glOrtho(-5, 5, -10, 10, 5, -5);
	gluLookAt(0.0, 0.0, 6.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	

	//ESFERA
	glPushMatrix();
	glTranslatef(0, 3, 0);
	glScalef(1.5, 1, 1);
	glRotatef(cubeAngle, 0, 0, 1);
	glRotatef(cubeAngle, 0, 1, 0);
	glRotatef(cubeAngle, 1, 0, 0);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glutSolidSphere(1.4, 30, 30);
	glPopMatrix();

	//CUBO
	glPushMatrix();
	glTranslatef(0,-0.3,0);
	glRotatef(cubeAngle, 0, 0, 1);
	glRotatef(cubeAngle, 0, 1, 0);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glutSolidCube(2);
	glPopMatrix();

	//ELIPSE
	glPushMatrix();
	glTranslatef(0, -3, 0);
	glScalef(0.8,0.25,0.2);
	glRotatef(cubeAngle, 0, 0, 1);
	glRotatef(cubeAngle, 0, 1, 0);
	glRotatef(cubeAngle, 1, 0, 0);
	glColor4f(1.0,1.0,1.0, 1.0);
	glutSolidSphere(3.5,30,30);
	glPopMatrix();

	//------------------------------------------------------------------------------------------------------------------
	//viewport en el que se van a mostrar los elementos del menu
	glViewport(10, 10, 1580, 200);
	glLoadIdentity();
	


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

	scaleCube[0] = 1.0;
	scaleCube[1] = 1.0;
	scaleCube[2] = 1.0;

	scaleSphere[0] = 1.0;
	scaleSphere[1] = 1.0;
	scaleSphere[2] = 1.0;

	scaleEllipse[0] = 1.0;
	scaleEllipse[1] = 0.5;
	scaleEllipse[2] = 1.0;
}

// Function for increasing the angle variable smoothly, 
// keeps it <=360
// It can also be implemented using the modulo operator.
void update(int value) {
	cubeAngle += 1.0f;
	ellipseAngle += 1.0f;
	menuAngle += 2.0f;

	if (menuAngle > 360) {
		menuAngle -= 360;
	}


	if (cubeAngle > 360) {
		cubeAngle -= 360;
	}

	if (ellipseAngle > 360) {
		ellipseAngle -= 360;
	}

	if (cubeMove) {
		for (int i = 0; i < cubes.size(); i++) {
			float z = cubes[i].posZ;

			if (z <= -27.0) {
				cubes[i].ida = false;
			} else if (z >= -10.0) {
				cubes[i].ida = true;
			}

			if (cubes[i].ida) {
				cubes[i].posZ -= 0.1f;
			} else {
				cubes[i].posZ += 0.1f;
			}
		}
	}

	if (sphereMove) {
		for (int i = 0; i < spheres.size(); i++) {
			float x = spheres[i].posX;

			if (x <= 0) {
				spheres[i].ida = false;
			} else if (x >= 10) {
				spheres[i].ida = true;
			}

			if (spheres[i].ida) {
				spheres[i].posX -= 0.1f;
				spheres[i].posZ += 0.3f;
			} else {
				spheres[i].posX += 0.1f;
				spheres[i].posZ -= 0.3f;
			}
		}
	}

	if (ellipseMove) {
		for (int i = 0; i < ellipses.size(); i++) {
			float y = ellipses[i].posY;

			if (y <= -1.5) {
				ellipses[i].ida = false;
			} else if (y >= 1.5) {
				ellipses[i].ida = true;
			}

			if (ellipses[i].ida) {
				ellipses[i].posX += 0.05f;
				ellipses[i].posY -= 0.05f;
				ellipses[i].posZ += 0.15f;
			} else {
				ellipses[i].posX -= 0.05f;
				ellipses[i].posY += 0.05f;
				ellipses[i].posZ -= 0.15f;
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
		x = randomFloat(-10, 10);
		y = randomFloat(-3.5, 3.5);
		z = randomFloat(-15.0, -10.0);
		r = randomFloat(0, 1);
		g = randomFloat(0, 1);
		b = randomFloat(0, 1);
		addCube(1, x, y, z, r, g, b, cubeTransparency);
		break;
	case 'S':
		x = randomFloat(-7.5, 7.5);
		y = randomFloat(-2.5, 2.5);
		z = randomFloat(-20.0, -7.0);
		r = randomFloat(0, 1);
		g = randomFloat(0, 1);
		b = randomFloat(0, 1);
		addSphere(0.5, 50, 50, x, y, z, r, g, b, sphereTransparency);
		break;
	case 'D':
		x = randomFloat(-5.0, 5.0);
		y = randomFloat(-3.0, 1.0);
		z = randomFloat(-20.0, -7.0);
		r = randomFloat(0, 1);
		g = randomFloat(0, 1);
		b = randomFloat(0, 1);
		addEllipse(0.75, 20, 10, x, y, z, r, g, b, ellipseTransparency);
		break;
	case 'M':
		cubeMove = !cubeMove;
		sphereMove = !sphereMove;
		ellipseMove = !ellipseMove;
		break;
	case 'E':
		scanf("%f %f %f", &cubeScale, &sphereScale, &ellipseScale);

		scaleCube[0] = cubeScale;
		scaleCube[1] = cubeScale;
		scaleCube[2] = cubeScale;

		scaleSphere[0] = sphereScale;
		scaleSphere[1] = sphereScale;
		scaleSphere[2] = sphereScale;

		scaleEllipse[0] = ellipseScale;
		scaleEllipse[1] = 0.5;
		scaleEllipse[2] = ellipseScale;
		break;
	case 'e':
		scaleCube[0] = 1.0;
		scaleCube[1] = 1.0;
		scaleCube[2] = 1.0;

		scaleSphere[0] = 1.0;
		scaleSphere[1] = 1.0;
		scaleSphere[2] = 1.0;

		scaleEllipse[0] = 1.0;
		scaleEllipse[1] = 0.5;
		scaleEllipse[2] = 1.0;
		break;
	case 'R':
		cubeRotate = !cubeRotate;
		ellipseRotate = !ellipseRotate;
		break;
	case 'C':
		for (int i = 0; i < cubes.size(); i++){
			cubes[i].color[0] = randomFloat(0, 1);
			cubes[i].color[1] = randomFloat(0, 1);
			cubes[i].color[2] = randomFloat(0, 1);
		}

		for (int i = 0; i < spheres.size(); i++) {
			spheres[i].color[0] = randomFloat(0, 1);
			spheres[i].color[1] = randomFloat(0, 1);
			spheres[i].color[2] = randomFloat(0, 1);
		}

		for (int i = 0; i < ellipses.size(); i++) {
			ellipses[i].color[0] = randomFloat(0, 1);
			ellipses[i].color[1] = randomFloat(0, 1);
			ellipses[i].color[2] = randomFloat(0, 1);
		}
		break;
	case 'T':
		scanf("%f %f %f", &cubeTransparency, &sphereTransparency, &ellipseTransparency);

		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].color[3] = cubeTransparency;
		}

		for (int i = 0; i < spheres.size(); i++) {
			spheres[i].color[3] = sphereTransparency;
		}

		for (int i = 0; i < ellipses.size(); i++) {
			ellipses[i].color[3] = ellipseTransparency;
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
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(0, 0);
	windowID = glutCreateWindow("OpenGL - Chaos");
	initRendering();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(draw);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutKeyboardFunc(keyboardCB);
	glutMainLoop();
	return 0;
}