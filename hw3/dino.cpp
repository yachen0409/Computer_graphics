#include "GL/glut.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

float range_x, range_y, range_z;
GLfloat cameraDistance = 3, cameraAngle = 0;
static int degree = 90;
static int oldPosY = -1;
static int oldPosX = -1;
class loader{
public:
    vector<vector<GLfloat>> v_sets;
    vector<vector<GLint>> index_sets;
    loader(string filename){
        ifstream file(filename);
        string line;
        float max_x, max_y, max_z;
        while (getline(file, line)){
            if (line.substr(0, 1) == "v"){
                vector<GLfloat> vertex;
                GLfloat x, y, z;
                stringstream file_line(line.substr(2));
                file_line >> x >> y >> z;
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                max_x=max(max_x, x);
                max_y=max(max_y, y);
                max_z=max(max_z, z);
                v_sets.push_back(vertex);
            }
            else if (line.substr(0, 1) == "f"){
                vector<GLint> vertex_index;
                GLint u, v, w;
                stringstream vtns(line.substr(2));
                vtns >> u; vtns >> v; vtns>> w;
                vertex_index.push_back(u-1);
                vertex_index.push_back(v-1);
                vertex_index.push_back(w-1);
                index_sets.push_back(vertex_index);
            }
        }
        range_x = max_x * 2;
        range_y = max_y * 2;
        range_z = max_z * 2;
        file.close();
    }
    void drawdino(){
        glColor3f(0, 0, 0);
        glBegin(GL_TRIANGLES);
            for (int i = 0; i < index_sets.size(); i++) {
                vector<GLfloat> normal_points(3);
                vector<GLfloat> points_set1(3);
                vector<GLfloat> points_set2(3);
                vector<GLfloat> points_set3(3);
                vector<GLfloat> points_temp1(3, 0); 
                vector<GLfloat> points_temp2(3, 0);
                vector<GLfloat> points_temp3(3, 0);
                GLint vertex_index1 = (index_sets[i])[0];
                GLint vertex_index2 = (index_sets[i])[1];
                GLint vertex_index3 = (index_sets[i])[2];
                
                points_set1[0] = (v_sets[vertex_index1])[0];
                points_set1[1] = (v_sets[vertex_index1])[1];
                points_set1[2] = (v_sets[vertex_index1])[2];
                points_set2[0] = (v_sets[vertex_index2])[0];
                points_set2[1] = (v_sets[vertex_index2])[1];
                points_set2[2] = (v_sets[vertex_index2])[2];
                points_set3[0] = (v_sets[vertex_index3])[0];
                points_set3[1] = (v_sets[vertex_index3])[1];
                points_set3[2] = (v_sets[vertex_index3])[2];
                
                points_temp1[0] = points_set1[0] - points_set2[0];
                points_temp1[1] = points_set1[1] - points_set2[1];
                points_temp1[2] = points_set1[2] - points_set2[2];
                points_temp2[0] = points_set1[0] - points_set3[0];
                points_temp2[1] = points_set1[1] - points_set3[1];
                points_temp2[2] = points_set1[2] - points_set3[2];
                points_temp3[0] = points_temp1[1] * points_temp2[2] - points_temp1[2] * points_temp2[1];
                points_temp3[1] = points_temp2[0] * points_temp1[2] - points_temp2[2] * points_temp1[0];
                points_temp3[2] = points_temp2[1] * points_temp1[0] - points_temp2[0] * points_temp1[1];

                GLfloat D = sqrt(pow(points_temp3[0], 2) + pow(points_temp3[1], 2) + pow(points_temp3[2], 2));
                normal_points[0] = points_temp3[0] / D;
                normal_points[1] = points_temp3[1] / D;
                normal_points[2] = points_temp3[2] / D;

                glNormal3f(normal_points[0], normal_points[1], normal_points[2]);
                glVertex3f(points_set1[0], points_set1[1], points_set1[2]);
                glVertex3f(points_set2[0], points_set2[1], points_set2[2]);
                glVertex3f(points_set3[0], points_set3[1], points_set3[2]);    
            }
        glEnd();
    }
};

class trackball{  
public:
    float phi = 0, theta = 90;
    int record_x = 0, record_y = 0;
    void calculate(int x, int y){
        float temp_theta = (float)(x-record_x) / 10;
        float temp_phi = (float)(y-record_y) / 10;
        theta += temp_theta;
        phi += temp_phi;
        if(phi > 360){
            phi-=360;
        }
        else if(phi < -360){
            phi += 360;
        }
        if(theta > 360){
            theta-=360;
        }
        else if(theta < -360){
            theta += 360;
        }
        record_x = x;
        record_y = y;
        // cout << phi << " " << theta<<endl;
    }
};
string filePath = "data/Dino.obj";
loader dinoobj = loader(filePath);
trackball ball;
void setLightRes() {
    glShadeModel(GL_SMOOTH);
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {1, 1, 1, 1.0};
    GLfloat light_specular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_position[] = {0.0f, 20.0f, 0.0f, 0.0f};

    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat high_shininess[] = {50.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (30, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void){
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    setLightRes();
    glPushMatrix(); 
    GLfloat eye_x = cameraDistance  * cos(ball.theta)* cos(ball.phi);
   	GLfloat eye_y = cameraDistance * sin(ball.phi);
    GLfloat eye_z = cameraDistance * sin(ball.theta)* cos(ball.phi);
    GLfloat camera_x = -cameraDistance * sin(ball.phi) * cos(ball.theta);
   	GLfloat camera_y = cameraDistance * cos(ball.phi);
    GLfloat camera_z = -cameraDistance * sin(ball.phi) * sin(ball.theta);
   	gluLookAt(eye_x, eye_y, eye_z, 0.0, 0.0, 0.0, camera_x, camera_y, camera_z);
    glScalef(1/range_y, 1/range_y, 1/range_y);
    dinoobj.drawdino();
    glPopMatrix();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN){
        if(button == GLUT_LEFT_BUTTON){
            ball.record_x = x;
            ball.record_y = y;
        }
    }
}
void move_trackball(int x, int y){
    ball.calculate(x, y);
}
void myIdle(){
    glutPostRedisplay();
}
int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Dino~");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightRes();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(move_trackball);
    glutIdleFunc(myIdle);
    glutMainLoop();
    return 0;
}
