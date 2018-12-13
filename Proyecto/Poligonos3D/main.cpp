#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using std::cout;
using std::endl;

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

float xInit, yInit, z, r, g, b;
float cubeTransparency = 1.0, sphereTransparency = 1.0, ellipseTransparency = 1.0, newScale = 1.0, newTransparency = 1.0;
float scaleCube[3], scaleSphere[3], scaleEllipse[3];
float cubeAngle = 0.0, ellipseAngle = 0.0, menuAngle = 0.0;
bool cubeRotate = false, cubeMove = false, sphereMove = false, ellipseRotate = false, ellipseMove = false;
int windowID;
int onMouse = 0;

std::vector<cube> cubes;
std::vector<sphere> spheres;
std::vector<sphere> ellipses;

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

//Fuentes: http://www.codersource.net/2011/01/27/displaying-text-opengl-tutorial-5/ https://www.opengl.org/resources/libraries/glut/spec3/node76.html
void drawBitmapText(char *string, float x, float y, float z){
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != ' '; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
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
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//para escribir el texto
	glPushMatrix();
		glColor3f(0, 0, 0);
	
		drawBitmapText("Escalar     ", -0.5, 0.0, 0.0);
		drawBitmapText("Mover     ", 0.0, 0.0, 0.0);
		drawBitmapText("Transparente     ", 0.5, 0.0, 0.0);
		drawBitmapText("Cambiar de Color     ", -0.5, -0.25, 0.0);
		drawBitmapText("Rotar     ", 0.0, -0.25, 0.0);
		drawBitmapText("Salir     ", 0.505, -0.25, 0.0);
		//drawBitmapText("     ", 0.0, 0.0, 0.0);
	
		//glColor3f(0.968, 0.498, 0.231);
		drawBitmapText("E     ", -0.6, 0.0, 0.0);
		drawBitmapText("M     ", -0.1, 0.0, 0.0);
		drawBitmapText("T     ", 0.4, 0.0, 0.0);
		drawBitmapText("C     ", -0.6, -0.25, 0.0);
		drawBitmapText("R     ", -0.10, -0.25, 0.0);
		drawBitmapText("Esc     ", 0.4, -0.25, 0.0);
		//drawBitmapText("     ", 0.0, 0.0, 0.0);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

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

void handleResize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float randomFloat(float min, float max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

bool dentroEsfera(int x, int y) {
	// X (106-261)
	// Y (45-245)
	bool res = 0;
	if (x>= 106 && x<=261 && y>=45 && y<= 245 ) {
		res = 1;
	}
	return res;
}

bool dentroElipsoide(int x, int y) {
	// x 83-538
	// y 473-592
	bool res = 0;
	if (x >= 83 && x <= 538 && y >= 473 && y <= 592) {
		res = 1;
	}
	return res;
}

bool dentroCubo(int x, int y) {
	// x 148-218
	// y 276-445
	bool res = 0;
	if (x >= 148 && x <= 218 && y >= 276 && y <= 445) {
		res = 1;
	}
	return res;
}

void keyboardCB(unsigned char key, int x, int y){
	switch (key){
	case 'M':
		if (onMouse == 1 && dentroCubo(x, y)) {
			cubeMove = !cubeMove;
		}

		if (onMouse == 1 && dentroEsfera(x, y)) {
			sphereMove = !sphereMove;
		}

		if (onMouse == 1 && dentroElipsoide(x, y)) {
			ellipseMove = !ellipseMove;
		}
		break;
	case 'C':
		if (onMouse == 1 && dentroCubo(x, y)) {
			for (int i = 0; i < cubes.size(); i++) {
				cubes[i].color[0] = randomFloat(0, 1);
				cubes[i].color[1] = randomFloat(0, 1);
				cubes[i].color[2] = randomFloat(0, 1);
			}
		}
		
		if (onMouse == 1 && dentroEsfera(x, y)) {
			for (int i = 0; i < spheres.size(); i++) {
				spheres[i].color[0] = randomFloat(0, 1);
				spheres[i].color[1] = randomFloat(0, 1);
				spheres[i].color[2] = randomFloat(0, 1);
			}
		}

		if (onMouse == 1 && dentroElipsoide(x, y)) {
			for (int i = 0; i < ellipses.size(); i++) {
				ellipses[i].color[0] = randomFloat(0, 1);
				ellipses[i].color[1] = randomFloat(0, 1);
				ellipses[i].color[2] = randomFloat(0, 1);
			}
		}
		break;
	case 'R':
		if (onMouse == 1 && dentroCubo(x, y)) {
			cubeRotate = !cubeRotate;
		}
		if (onMouse == 1 && dentroElipsoide(x, y)) {
			ellipseRotate = !ellipseRotate;
		}
		break;
	case 'E':
		if (onMouse == 1 && dentroCubo(x, y)) {
			scanf("%f", &newScale);
			if (newScale > 0) {
				scaleCube[0] = newScale;
				scaleCube[1] = newScale;
				scaleCube[2] = newScale;
			}
		}

		if (onMouse == 1 && dentroEsfera(x, y)) {
			scanf("%f", &newScale);
			if (newScale > 0) {
				scaleSphere[0] = newScale;
				scaleSphere[1] = newScale;
				scaleSphere[2] = newScale;
			}
		}

		if (onMouse == 1 && dentroElipsoide(x, y)) {
			scanf("%f", &newScale);
			if (newScale > 0) {
				scaleEllipse[0] = newScale;
				scaleEllipse[1] = 0.5;
				scaleEllipse[2] = newScale;
			}
		}
		break;
	case 'T':
		if (onMouse == 1 && dentroCubo(x, y)) {
			scanf("%f", &newTransparency);
			if (newTransparency >= 0 && newTransparency <= 1) {
				cubeTransparency = newTransparency;
				for (int i = 0; i < cubes.size(); i++) {
					cubes[i].color[3] = cubeTransparency;
				}
			}
		}

		if (onMouse == 1 && dentroEsfera(x, y)) {
			scanf("%f", &newTransparency);
			if (newTransparency >= 0 && newTransparency <= 1) {
				sphereTransparency = newTransparency;
				for (int i = 0; i < spheres.size(); i++) {
					spheres[i].color[3] = sphereTransparency;
				}
			}
		}

		if (onMouse == 1 && dentroElipsoide(x, y)) {
			scanf("%f", &newTransparency);
			if (newTransparency >= 0 && newTransparency <= 1) {
				ellipseTransparency = newTransparency;
				for (int i = 0; i < ellipses.size(); i++) {
					ellipses[i].color[3] = ellipseTransparency;
				}
			}
		}
		break;
	case 27: // Escape key
		glutDestroyWindow(windowID);
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void mouseClicks(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (dentroCubo(x, y)) {
			xInit = randomFloat(-10, 10);
			yInit = randomFloat(-3.5, 3.5);
			z = -15.0;
			r = randomFloat(0, 1);
			g = randomFloat(0, 1);
			b = randomFloat(0, 1);
			addCube(1, xInit, yInit, z, r, g, b, cubeTransparency);
		}

		if (dentroEsfera(x, y)) {
			xInit = randomFloat(-10.0, 10.0);
			yInit = randomFloat(-2.5, 2.5);
			z = -15.0;
			r = randomFloat(0, 1);
			g = randomFloat(0, 1);
			b = randomFloat(0, 1);
			addSphere(0.5, 50, 50, xInit, yInit, z, r, g, b, sphereTransparency);
		}

		if (dentroElipsoide(x, y)) {
			xInit = randomFloat(-10.0, 10.0);
			yInit = randomFloat(-3.0, 1.0);
			z = -15.0;
			r = randomFloat(0, 1);
			g = randomFloat(0, 1);
			b = randomFloat(0, 1);
			addEllipse(0.75, 20, 10, xInit, yInit, z, r, g, b, ellipseTransparency);
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		onMouse = 1;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		onMouse = 0;
	}
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
	glutMouseFunc(mouseClicks);
	glutMainLoop();
	return 0;
}