#include <gl/glut.h>
#include <bits/stdc++.h>
#define PI 3.1415926
using namespace std;
int width=1000, height=800;
float R = 30, r = 0, horizontal = 0, temphorizontal = 0, vertical = 0, tempvertical = 0, sen = 500, velocity =1, radx = 0, rady = 0;
float lookx = 0, looky = 0, lookz = R, movex = 0, movey = 0, movez = 0;
float propellerangle = 0, theta = 0, ROVdirectionangle = 0;
float perx = 0, pery = 0;
float paw = 0, random = 0, random2 = 0, grassrandlocx[400] = { 0 }, grassrandlocz[400] = { 0 }, grassrandheight[400] = { 0 }, grassrandcolor[400][3] = { 0 };
float stonerandlocx[400] = { 0 }, stonerandlocz[40] = { 0 }, stonerandsize[40] = { 0 }, stonerandrotate[40] = { 0 },stonerandheight[40];
float fishrandlocx[40] = { 0 }, fishrandlocz[40] = { 0 }, fishrandrotate[40], fishrandsize[40] = {0}, fishrandheight[40] = { 0 };
float u = 0;

void light() {
	GLfloat ambient[] = { 0.5, 0.8, 0.1, 0.1 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { -80.0, 50.0, 25.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat local_view[] = { 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
//World
void Drawsea() {
	glColor3f(10 / 255.0,148 / 255.0,245/255.0);
	glutSolidSphere(10000, 10, 10);
	glColor3f(30 / 255.0, 50 / 255.0, 60 / 255.0);
	glPushMatrix();
	glTranslatef(0, -8000, 0);
	glutSolidCube(10000);
	glPopMatrix();
}
void Drawworldxy() {
	glPushMatrix();
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex3f(-1000,-0.9,0);
	glVertex3f(1000, -0.9,0);
	glColor3f(0, 1, 0);
	glVertex3f(0, -0.9, -1000);
	glVertex3f(0, -0.9, 1000);
	glColor3f(1, 1, 1);
	glVertex3f(0, -1000, 0);
	glVertex3f(0, 1000, 0);
	glEnd();
	glPopMatrix();
}
void Drawflat() {
	glColor3f(0, 0, 0.3);
	glPushMatrix();
	
	glBegin(GL_POLYGON); {
		glVertex3f(-1000, -1, -1000);
		glColor3f(0, 0.3, 0);
		glVertex3f(-1000, -1, 1000);
		glColor3f(0.3, 0, 0);
		glVertex3f(1000, -1, 1000);
		glColor3f(1, 1, 1);
		glVertex3f(1000, -1, -1000);
	}
	glEnd();
	glPopMatrix();
}
void Drawgrass() {
	glColor3f(0, 1, 0);
	glPointSize(20);
	glPushMatrix();
	glBegin(GL_LINES);
	float j = 0;
	for (int count = 0; count < 100; count++) {
		float r1 = grassrandlocx[count];
		float r2 = grassrandlocz[count];
		float temp = (float)(rand() % 1000) / 1000;
		glColor3f(grassrandcolor[count][0], grassrandcolor[count][1], grassrandcolor[count][2]);
			for (int i = 0; i <grassrandheight[count]; i +=1){
				glVertex3f(r1, i, r2 + 2 * cos(j+random));
				j += 30*PI/360;
				glVertex3f(r1, i + 0.999, r2 + 2 * cos(j+random));
			}
		j += PI / 360;
	}
	//cout << grassrandheight[0]<<" "<<grassrandlocx[0]<<" "<<grassrandlocz[0]<<endl;
	glEnd();
	glPopMatrix();
}
void Drawstone() {
	glColor3f(0.627,0.392,0.117);
	for (int i = 0; i < 40; i++) {
		glPushMatrix();
		glRotated(stonerandrotate[i],0,1,0);
		glTranslatef(stonerandlocx[i], 0, stonerandlocz[i]);
		glutSolidCone(stonerandheight[i],stonerandsize[i],5,5);
		glPopMatrix();
	}
	
}
void Drawfish() {

	for (int i = 0; i < 10;i++) {
		glPushMatrix();
		glTranslatef(fishrandlocx[i], fishrandheight[i], fishrandlocz[i]);
		glRotatef(fishrandrotate[i], 0, 1, 0);

		glPushMatrix();
		glutSolidTeapot(fishrandsize[i]);
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		glTranslatef(0, 0.1, 0);
		glutSolidTeapot(fishrandsize[i]);
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();
	}
}
void Drawworld() {
	cout << "x: " << movex << " y: "<<-movey<<" z:" << movez << " velocity: "<<velocity<<"\n ";// << unitmovex << " " << unitmovez << " " << unitmovex / unitmovez << " " << movex / movez << "\n";
	
	if (movex * velocity < -1000) {//border
		movex = -999/velocity;
	}
	else if (movex * velocity > 1000) {
		movex = 999 / velocity;
	}
	if (movez * velocity < -1000) {
		movez = -999 / velocity;
	}
	else if (movez * velocity > 1000) {
		movez = 999 / velocity;
	}
	Drawsea();
	glPushMatrix();
	glTranslatef(movex * velocity, -1+movey*velocity, movez * velocity);
	Drawflat();
	Drawworldxy();
	random += 3*PI/360;
	Drawgrass();
	Drawstone();
	Drawfish();
	light();
	glPopMatrix();
}
void Draworigincube() {
	//cout << "atan" << atan(lookz / lookx)*180/PI<<"\n";
	glPushMatrix();

	glRotatef(-atan(lookz / lookx) * 180 / PI,0,1,0);

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(1, 1, 1); glVertex3f(-1, 1, 1); glVertex3f(-1, -1, 1); glVertex3f(1, -1, 1);//z
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, -1); glVertex3f(-1, 1, -1);glVertex3f(-1, -1, -1);  glVertex3f(1, -1, -1);//-z
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(1, -1, 1); glVertex3f(1, -1, -1); glVertex3f(1, 1, -1); glVertex3f(1, 1, 1);//x
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-1, -1, -1);glVertex3f(-1, 1, -1);glVertex3f(-1, 1, 1); glVertex3f(-1, -1, 1);  //-x
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(1, -1, -1);glVertex3f(1, -1, 1); glVertex3f(-1, -1, 1);glVertex3f(-1, -1, -1);//-y
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1); glVertex3f(-1, 1, 1); glVertex3f(-1, 1, -1); glVertex3f(1, 1, -1); //y
	glEnd();

	glPopMatrix();
}
void Drawxyz() {
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-1000, 0, 0);
	glVertex3f(1000, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0,-1000,  0);
	glVertex3f(0,1000,  0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -1000);
	glVertex3f(0, 0, 1000);
	glEnd();
}
//ROV
void Drawpropeller() {
	glColor3f(0.196, 0.235, 0.313);
	glPushMatrix();
	glTranslatef(3.2,0.5, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(propellerangle, 0, 1, 0);
		glPushMatrix();
			glRotatef(180, 1, 0, 0);//reverse
			glTranslatef(1.5, 0, -0.85);
			glRotatef(210, 0, 1, 0);
			glutWireTeapot(1);
		glPopMatrix();
		glPushMatrix();
			glRotatef(180, 1, 0, 0);
			glTranslatef(-1.5, 0, -0.85);
			glRotatef(330, 0, 1, 0);
			glutWireTeapot(1);
		glPopMatrix();
		glPushMatrix();
			glRotatef(180, 1, 0, 0);
			glTranslatef(0, 0, 1.7);
			glRotatef(90, 0, 1, 0);
			glutWireTeapot(1);
		glPopMatrix();
	glPopMatrix();
}
void Drawbody() {
	glColor3f(0.156, 0.313, 0.117);
	glPushMatrix();
		glScalef(2, 1, 1);
		GLdouble eqn[4] = { -1,0,0,0.5 };
		glClipPlane(GL_CLIP_PLANE4, eqn);
		glEnable(GL_CLIP_PLANE4);
		glutSolidSphere(1, 20, 20);
		glDisable(GL_CLIP_PLANE4);
	glPopMatrix();
	glPushMatrix();
		GLdouble eqn2[4] = { 1,0,0,0 };
		glClipPlane(GL_CLIP_PLANE0, eqn2);
		glEnable(GL_CLIP_PLANE0);
		glScalef(2, 1, 1);
		glutSolidTeapot(1);
		glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
}
void Drawarm() {
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();//stick
	glTranslatef(-2.8, 0, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.2, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();//paw
		glTranslatef(-3.7, 0, 0);
		glPushMatrix();
			glRotatef(45+paw, 0, 1, 0);
			glPushMatrix();
			glTranslatef(0.1,0,-0.5);
			glRotated(-90, 1, 0, 0);
			glScalef(0.2, 1, 0.05);
			glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glRotatef(-45-paw, 0, 1, 0);
			glPushMatrix();
			glTranslatef(0.1, 0, 0.5);
			glRotated(90, 1, 0, 0);
			glScalef(0.2, 1, 0.05);
			glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void Drawcamera() {
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(0, 1.4, 0);
	glScaled(0.3, 1, 0.3);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glScaled(0.1, 0.2, 0.2);
	glTranslated(-1.8,8.5, 0);
	glutSolidCube(1);
	glPopMatrix();
}
void DrawROV() {
	theta = -atan(lookz / lookx) * 180 / PI;
	if (theta < 0)theta += 360;
	else if (theta > 360)theta -= 360;
	if (lookz < 0 && lookx < 0)ROVdirectionangle = theta + 180;
	else if (lookz> 0 && lookx < 0)ROVdirectionangle =theta+180;
	else ROVdirectionangle = theta;
	//cout << lookz<<" "<<lookx<<" "<<ROVdirectionangle << "\n";
	glPushMatrix();
	glRotatef(ROVdirectionangle, 0, 1, 0);
	Drawpropeller();
	Drawbody();
	Drawarm();
	Drawcamera();
	glPopMatrix();
	
}
void Draw() {
	glPushMatrix();
	glScalef(30 / R, 30 / R, 30 / R);
	glRotatef(perx, 0, 1, 0);
	Drawworld();
	//Drawxyz();
	//Draworigincube();
	DrawROV();
	glPopMatrix();
};
//Main
void Init() {
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.117, 0.352, 0.666,0);
	srand(time(NULL));
	random = rand();
	random2 = rand();
	for (int i = 0; i < 100; i++) {//grass
		grassrandlocx[i] = rand() % 2000 - 1000;
		grassrandlocz[i] = rand() % 2000 - 1000;
		grassrandheight[i] = rand() % 1000+1;
		for (int j = 0; j < 400; j++) {
			grassrandcolor[i][0] = rand() % 255 / 255.0;
			grassrandcolor[i][1] = rand() % 255 / 255.0;
			grassrandcolor[i][2] = rand() %255 / 255.0;
		}
	}
	for (int i = 0; i < 40; i++) {
		stonerandlocx[i] = rand() % 2000 - 1000;
		stonerandlocz[i] = rand() % 2000 - 1000;
		stonerandsize[i] = rand() % 200 + 1;
		stonerandheight[i] = rand() % 100 + 1;
		stonerandrotate[i] = rand() % 360;
	}
	for (int i = 0; i < 10; i++) {
		fishrandlocx[i] = rand() % 1500 - 750;
		fishrandlocz[i] = rand() % 1500 - 750;
		fishrandsize[i] = rand() % 3 + 1;
		fishrandheight[i] = rand() % 500 + 1;
		fishrandrotate[i] = rand() % 360;
	}
	glutPostRedisplay();
	//light();
}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glLoadIdentity();
	gluLookAt(lookx, looky, lookz,  0, 0, 0,  0, 1, 0);
	Draw();
	glutSwapBuffers();
	glutPostRedisplay();
}
void Reshape(int w,int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w/ (GLfloat)h,1.0,10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Keyboard(unsigned char key,int x,int y) {
	//cout << key << "\n";
	if (key == 27)exit(0);
	else if (key == 'a' || key == 'A') {
		movex -= (lookx * cosf(PI / 2) - lookz * sinf(PI / 2)) / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;//To normalize vector
		movez -= (lookx * sinf(PI / 2) + lookz * cosf(PI / 2)) / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;
		propellerangle += 3;
	}
	else if (key == 'd' || key == 'D') {
		movex += (lookx * cosf(PI / 2) - lookz * sinf(PI / 2)) / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;
		movez += (lookx * sinf(PI / 2) + lookz * cosf(PI / 2)) / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;
		propellerangle -= 3;
	}
	else if (key == 'w' || key == 'W') {
		movex += lookx / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;
		movez += lookz / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;
		propellerangle += 30;
	}
	else if (key == 's' || key == 'S') {
		movex -= lookx / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;
		movez -= lookz / sqrt(pow(lookx, 2) + pow(lookz, 2)) * velocity;
		propellerangle -= 30;
	}
	else if (key == 'i' || key == 'I') {

	}
	else if (key == 'j' || key == 'J') {//use in ROV
		perx += 3;
	}
	else if (key == 'l' || key == 'L') {
		perx -= 3;
	}
	else if (key == 'z' || key == 'Z') {
		if (movey < 0) {
			movey += 10;
			propellerangle += 10;
		}
	}
	else if (key == 'x' || key == 'X') {
		if (movey > -1000) {
			movey -= 10;
			propellerangle -= 10;
		}
	}
	else if (key == '+') {
		if (velocity < 10) {// speed
			velocity += 0.5;
		}
	}
	else if (key == '-') {
		if (velocity > 1) {// speed
			velocity -=  0.5 ;
		}
	}
	else if (key == 't') {
		u += 0.1;
	}
	else if (key == 'y') {
		u -= 0.1;
	}
	//cout << velocityx << " " << velocityz <<" "<< movex * accelerate << endl;
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y) {
	//cout << "M: " << button << " " << state << "\n";
	if (button == 0) {
		if (state == 0)
			paw =43;
		else
			paw = 0;
	}
	else if (button == 3) {
		R -= R < 2 ? 0 : 1;
	}
	else if (button == 4) {
		R += 1;
	}
	glutPostRedisplay();
}
void Passmotion(int x, int y) {
	horizontal += width / 2 - x;
	vertical += height / 2 - y;
	radx = horizontal / 509.55414;//800 horizontal = 90 degree = PI/2
	rady = vertical / 509.55414;
	//Y
	if (rady < 0.01) {//y = R;
		rady = 0.05;
		vertical = 10;
	}
	else if (rady > 1.56) {//y = 0
		rady = 1.55;
		vertical = 795;
	}
	looky = R * cosf(rady);
		r = R * sinf(rady);
	//X
	if (radx < -6.283185 || radx > 6.283185) {
		radx = 0;
		horizontal = 0;
	}
	lookz = r * cosf(radx);
	lookx = r * sinf(radx);
	//cout << "T: " << radx << " " << horizontal << " " << lookx << " " << looky << " " << lookz << "\n";
	glutPostRedisplay();
	glutWarpPointer(width / 2, height / 2);
}
void timerProc(int d) {//440 fps
	Display();
	glutTimerFunc(7, timerProc, 1);
}
int main(int argc,char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);

	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Passmotion);
	glutTimerFunc(7, timerProc, 1);//fps
	glutMainLoop();
}
