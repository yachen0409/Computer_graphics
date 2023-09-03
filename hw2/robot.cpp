#include "GL/glut.h"
#include <iostream>
#include <cmath>
using namespace std;

GLfloat cameraDistance = 10, cameraAngle = 0;
// {head, left_shoulder, right_shoulder, left_elbow, right_elbow, left_foot, right_foot, left_knee, right_knee}
int robot_angles[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void change_angle(int angle, int delta, int minimum = 0, int maximum = 180){
    robot_angles[angle] = (robot_angles[angle] + delta) % 360;
	int standard = robot_angles[angle];
    robot_angles[angle] = max(robot_angles[angle], minimum);
    robot_angles[angle] = min(robot_angles[angle], maximum);
	if(robot_angles[angle] != standard){
		cout << "MAX/MIN angle acheive!! Try Another Direction~" << endl;
	}
}
void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}
// TORSO
void specialKeys(int key, int x, int y){
    GLfloat angleDelta = 5 * M_PI / 180.0;
    if(key == GLUT_KEY_LEFT){
        cameraAngle -= angleDelta;
    }
    if(key == GLUT_KEY_RIGHT){
        cameraAngle += angleDelta;
    }
    glutPostRedisplay();
}
void display(void){
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glLoadIdentity();
	//TORSO
   	GLfloat x = cameraDistance * sin(cameraAngle);
   	GLfloat z = cameraDistance * cos(cameraAngle);
   	gluLookAt(x, 0.7, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//HEAD
	glPushMatrix();		
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0.0, 2.15, 0.0);
		glPushMatrix();
   			glScalef(0.35, 0.35, 0.35);
   			glutSolidCube (1);
   		glPopMatrix();
		glRotatef((GLfloat) robot_angles[0], 0.0, 0.0, 1.0);
		glColor3f(1.0f, 0.5f, 0.0f);
		glTranslatef(0.0, 0.7, 0.0);
		glutSolidSphere(0.7f, 40, 40);
	glPopMatrix();
	//BODY
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glScalef(2.0, 4.0, 1.0);
		glutSolidCube (1.0);
	glPopMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glPushMatrix();
		glScalef(2.0, 4.0, 1.0);
		glutWireCube (1.0);
	glPopMatrix();
	//LEFT ARM
	glPushMatrix();		
		glColor3f(0.5f, 0.0f, 0.5f);
   		glTranslatef(-0.7, 1.7, 0.0);
   		glRotatef((GLfloat) robot_angles[1], 0.0, 0.0, 1.0);
   		glTranslatef(-1.0, 0.0, 0.0);
   		glPushMatrix();
   			glScalef(1.5, 0.4, 0.5);
   			glutSolidCube (1.0);
   		glPopMatrix();

		glColor3f(0.0f, 0.0f, 1.0f);
   		glTranslatef(-0.8, 0.0, 0.0);
   		glRotatef((GLfloat) robot_angles[3], 0.0, 0.0, 1.0);
   		glTranslatef(-0.8, 0.0, 0.0);
   		glPushMatrix();
   			glScalef(2.0, 0.4, 0.5);
   			glutSolidCube (1.0);
   		glPopMatrix();
   	glPopMatrix();
	//RIGHT ARM
	glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.5f);
   		glTranslatef(0.7, 1.7, 0.0);
   		glRotatef((GLfloat) robot_angles[2], 0.0, 0.0, 1.0);
   		glTranslatef(1.0, 0.0, 0.0);
   		glPushMatrix();
   			glScalef(1.5, 0.4, 0.5);
   			glutSolidCube (1.0);
   		glPopMatrix();

		glColor3f(0.0f, 0.0f, 1.0f);
   		glTranslatef(0.8, 0.0, 0.0);
   		glRotatef((GLfloat) robot_angles[4], 0.0, 0.0, 1.0);
   		glTranslatef(0.8, 0.0, 0.0);
   		glPushMatrix();
   			glScalef(2.0, 0.4, 0.5);
   			glutSolidCube (1.0);
   		glPopMatrix();
	glPopMatrix();
	//LEFT FOOT
	glPushMatrix();		
		glColor3f(0.2f, 0.7f, 0.2f);
   		glTranslatef(-0.8, -1.5, 0.0);
   		glRotatef((GLfloat) robot_angles[5], 1, 0.0, 0.0);
   		glTranslatef(0.0, -1.2, 0.0);
   		glPushMatrix();
   			glScalef(0.7, 1.5, 0.7);
   			glutSolidCube (1.0);
   		glPopMatrix();

		glColor3f(0.7f, 0.2f, 0.2f);
   		glTranslatef(0.0, -0.7, 0.0);
   		glRotatef((GLfloat) robot_angles[7], 1, 0.0, 0.0);
   		glTranslatef(0.0, -1.0, 0.0);
   		glPushMatrix();
   			glScalef(0.7, 2.0, 0.7);
   			glutSolidCube (1.0);
   		glPopMatrix();
   	glPopMatrix();
	//RIGHT FOOT
	glPushMatrix();		
		glColor3f(0.2f, 0.7f, 0.2f);
   		glTranslatef(0.8, -1.5, 0.0);
   		glRotatef((GLfloat) robot_angles[6], 1, 0.0, 0.0);
   		glTranslatef(0.0, -1.2, 0.0);
   		glPushMatrix();
   			glScalef(0.7, 1.5, 0.7);
   			glutSolidCube (1.0);
   		glPopMatrix();

		glColor3f(0.7f, 0.2f, 0.2f);
   		glTranslatef(0.0, -0.7, 0.0);
   		glRotatef((GLfloat) robot_angles[8], 1, 0.0, 0.0);
   		glTranslatef(0.0, -1.0, 0.0);
   		glPushMatrix();
   			glScalef(0.7, 2.0, 0.7);
   			glutSolidCube (1.0);
   		glPopMatrix();
   	glPopMatrix();
   	glutSwapBuffers();
}
void reshape(int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -5.0);
}
void keyboard(unsigned char key, int x, int y){
	int delta = 3;
   	switch (key) {
		//HEAD -> q/Q
		case 'q':
			change_angle(0, delta, -45, 45);
			glutPostRedisplay();
			break;
		case 'Q':
			change_angle(0, -delta, -45, 45);
			glutPostRedisplay();
			break;
		//LEFT_SHOULDER -> w/W
		case 'w':
			change_angle(1, -delta, -90, 75);
         	glutPostRedisplay();
         	break;
      	case 'W':
			change_angle(1, delta, -90, 75);
         	glutPostRedisplay();
         	break;
		//RIGHT_SHOULDER -> e/E
      	case 'e':
			change_angle(2, delta, -75, 90);
         	glutPostRedisplay();
         	break;
      	case 'E':
			change_angle(2, -delta, -75, 90);
         	glutPostRedisplay();
         	break;
		//LEFT_ELBOW -> s/S
	  	case 's':
			change_angle(3, -delta, -90, 90);
			glutPostRedisplay();
			break;
		case 'S':
			change_angle(3, delta, -90, 90);
			glutPostRedisplay();
			break;
		//RIGHT_ELBOW -> d/D
		case 'd':
			change_angle(4, delta, -90, 90);
			glutPostRedisplay();
			break;
		case 'D':
			change_angle(4, -delta, -90, 90);
			glutPostRedisplay();
			break;
		//LEFT_FOOT -> r/R
		case 'r':
			change_angle(5,-delta, -160, 90);
			glutPostRedisplay();
			break;
		case 'R':
			change_angle(5, delta, -160, 90);
			glutPostRedisplay();
			break;
		//RIGHT_FOOT -> t/T
		case 't':
			change_angle(6, -delta, -160, 90);
			glutPostRedisplay();
			break;
		case 'T':
			change_angle(6, delta, -160, 90);
			glutPostRedisplay();
			break;
		//LEFT_KNEE -> f/F		
		case 'f':
			change_angle(7, -delta, 0, 135);
			glutPostRedisplay();
			break;
		case 'F':
			change_angle(7, delta, 0, 135);
			glutPostRedisplay();
			break;
		//RIGHT_KNEE -> g/G				
		case 'g':
			change_angle(8, -delta, 0, 135);
			glutPostRedisplay();
			break;
		case 'G':
			change_angle(8, delta, 0, 135);
			glutPostRedisplay();
			break;
		// QUIT -> esc		
		case 27:
			exit(0);
			break;
		default:
			cout << "Press other key to manipulate the robot!" << endl;
			break;
   }
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ROBOT_109550073");
	init();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardUpFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
