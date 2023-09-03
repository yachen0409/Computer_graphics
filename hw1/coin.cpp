#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

stringstream scoreStream;
clock_t tStart, tStart2, tStart3, tStart4, tStart5;
bool firstwindisplay = true, firstlosedisplay = true, entergame = false;
int final_score = 0, record = 0, score = 0;
string output_time;
fstream readfile, writefile;

//catcher defination
double catcher_x = -10;
double catcher_y = -10;
void catcher(){
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);        
        glVertex2f(catcher_x, catcher_y+2);
        glVertex2f(catcher_x+3, catcher_y+2);
        glVertex2f(catcher_x+3, catcher_y);
        glVertex2f(catcher_x, catcher_y);
    glEnd();
}
void catcher_reshape(int catcher_x, int catcher_y){
    glViewport(0, 0, catcher_x, catcher_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, +10, -10, +10);
    glMatrixMode(GL_MODELVIEW);
}
//catcher move control
void catcher_move_func(int key, int a, int b){
    if(key==102 && catcher_x<7){
        catcher_x+=0.5;
    }
    if(key == 100 && catcher_x >= -9){
        catcher_x-=0.5;
    }
}

//yellow coin defination
double coin_x = rand()%10+-10;
double coin_y = 9;
void coin(){
    float theta;
    glBegin(GL_POLYGON);
        glColor3f(1, 1, 0);
        for(int i = 0; i < 360; ++i){
            theta = i*3.142/180;
            glVertex2d(coin_x+1*cos(theta), coin_y+1*sin(theta));
        }
    glEnd();
}
void coin_reshape(int coin_x, int coin_y){
    glViewport(0, 0, coin_x, coin_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, +10, -10, +10);
    glMatrixMode(GL_MODELVIEW);
}
double coinrepeat_x = rand()%10;
double coinrepeat_y = 9;
void coinrepeat(){
    float theta;
    glBegin(GL_POLYGON);
        glColor3f(1, 1, 0);
        for(int i = 0; i < 360; ++i){
            theta = i*3.142/180;
            glVertex2d(coinrepeat_x+1*cos(theta), coinrepeat_y+1*sin(theta));
        }
    glEnd();
}
void coinrepeat_reshape(int coinrepeat_x, int coinrepeat_y){
    glViewport(0, 0, coinrepeat_x, coinrepeat_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, +10, -10, +10);
    glMatrixMode(GL_MODELVIEW);
}

//orange coin defination
double coin2_x = rand()%20+-10;
double coin2_y = 9.5;
void coin2(){
    float theta;
    glBegin(GL_POLYGON);
        glColor3f(1, 0.5, 0);
        for(int i = 0; i < 360; ++i){
            theta = i*3.142/180;
            glVertex2d(coin2_x+0.5*cos(theta), coin2_y+0.5*sin(theta));
        }
    glEnd();
}
void coin2_reshape(int coin2_x, int coin2_y){
    glViewport(0, 0, coin2_x, coin2_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, +10, -10, +10);
    glMatrixMode(GL_MODELVIEW);
}

//rainbow star defination
double star_x = rand()%18-9.4;
double star_y = 9.3;
bool star_goes_left = true;
void star(){
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(star_x, star_y+0.7, 0); // <--- -0.60 instead of -0.68
    glColor3f(1, 0.5, 0);
    glVertex3f(star_x+0.6, star_y+0.4, 0); // <--- -0.68 instead of -0.60
    glColor3f(1, 1, 0);
    glVertex3f(star_x+0.6, star_y-0.4, 0);
    glColor3f(0, 1, 0);
    glVertex3f(star_x, star_y-0.7, 0);
    glColor3f(0, 0, 1);
    glVertex3f(star_x-0.6, star_y-0.4, 0);
    glColor3f(1, 0, 1);
    glVertex3f(star_x-0.6, star_y+0.4, 0);
    glEnd();
}
void star_reshape(int star_x, int star_y){
    glViewport(0, 0, star_x, star_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, +10, -10, +10);
    glMatrixMode(GL_MODELVIEW);
}

//stone defination
double stone_x = rand()%20+-10;
double stone_y = 9;
void stone(){
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2f(stone_x, stone_y+1);
        glVertex2f(stone_x+1, stone_y+1);
        
        glVertex2f(stone_x+1, stone_y);
        glVertex2f(stone_x, stone_y);
    glEnd();
    glColor3f(1, 1, 1);

}
void stone_reshape(int stone_x, int stone_y){
    glViewport(0, 0, stone_x, stone_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, +10, -10, +10);
    glMatrixMode(GL_MODELVIEW);
}

// game info display
void display_score(void){
    char buf[256];
    sprintf(buf, "Score: %d", score);
    glRasterPos2i(-2, 9.7);
    glColor3f(1, 1, 1);
    for(int i = 0; i < strlen(buf); ++i){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[i]);
    }
    glColor3f(1, 1, 0);
    if((clock() - tStart2)*10.0/CLOCKS_PER_SEC < 0.5){
        glRasterPos2i(5, 9.6);
        
        char msg1[] = "+1";
        for(int i = 0; i < strlen(msg1); ++i){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg1[i]);
        }
    }
    glColor3f(1, 0.5, 0);
    if((clock() - tStart3)*10.0/CLOCKS_PER_SEC < 0.5){
        glRasterPos2i(6, 9.5);
        
        char msg2[] = "+2";
        for(int i = 0; i < strlen(msg2); ++i){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg2[i]);
        }
    }
    glColor4f(0, 1, 1, 1);
    if((clock() - tStart4)*10.0/CLOCKS_PER_SEC < 0.5){
        glRasterPos2i(7, 9.4);
        
        char msg3[] = "+5";
        for(int i = 0; i < strlen(msg3); ++i){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg3[i]);
        }
    }
    glColor3f(0.7, 0.7, 0.7);
    if((clock() - tStart5)*10.0/CLOCKS_PER_SEC < 0.5){
        glRasterPos2i(8, 9.3);
        
        char msg4[] = "-2";
        for(int i = 0; i < strlen(msg4); ++i){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg4[i]);
        }
    }
}
void display_remain_time()
{
    stringstream temp;
    temp << (double)(30.0-(clock() - tStart)*10.0/CLOCKS_PER_SEC);
    string output;
    temp >> output;
    if(stoi(output) > 10){
        glColor3f(0, 1, 0); //green
    }
    else{
        glColor3f(1, 0, 0); //red
    }
    glRasterPos2f(-9, 9);
    char msg1[] = "Time:";
    for(int i = 0; i < strlen(msg1); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg1[i]);
    }
    for (string::iterator i = output.begin(); i != output.end(); ++i)
    {
      char c = *i;
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 's');
}

//welcome page
void welcomeDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tStart = clock();
    glColor3f(1, 1, 0);
    glRasterPos3f(-3.5,7,0);
    char line1[] = "$$$$$$$$$$$$$$$$";
    for(int i = 0; i < strlen(line1); ++i){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, line1[i]);
    }
    glRasterPos3f(-3.5,6,0);
    char line2[] = "$$ Coin Catcher $$";
    for(int i = 0; i < strlen(line2); ++i){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, line2[i]);
    }
    glRasterPos3f(-3.5,5,0);
    // $$$$$$$$$$$$$$$$
    for(int i = 0; i < strlen(line1); ++i){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, line1[i]);
    }
    glColor3f(1,1,1);
    glRasterPos3f(-3.5,3,0);
    char line4[] = "Collect all coins and Avoid stones!";
    for(int i = 0; i < strlen(line4); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line4[i]);
    }
    glColor3f(1,1,1);
    glRasterPos3f(-3,2,0);
    char line5[] = "---------------------";
    for(int i = 0; i < strlen(line5); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line5[i]);
    }
    glColor3f(1,1,0);
    glRasterPos3f(-2,1,0);
    char line6[] = "YELLOW COINS -> +1";
    for(int i = 0; i < strlen(line6); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line6[i]);
    }
    glColor3f(1,0.5,0);
    glRasterPos3f(-2,0,0);
    char line7[] = "ORANGE COINS -> +2";
    for(int i = 0; i < strlen(line7); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line7[i]);
    }
    glColor4f(0, 1, 1, 1);
    glRasterPos3f(-2.2,-1,0);
    char line8[] = "RAINBOW STARS -> +5";
    for(int i = 0; i < strlen(line8); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line8[i]);
    }
    glColor3f(0.8, 0.8, 0.8);
    glRasterPos3f(-1.8,-2,0);
    char line9[] = "GREY STONES -> -3";
    for(int i = 0; i < strlen(line9); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line9[i]);
    }
    //---------------------
    glColor3f(1,1,1);
    glRasterPos3f(-3,-3,0);
    for(int i = 0; i < strlen(line5); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line5[i]);
    }
    glColor3f(1,0,0);
    glRasterPos3f(-3.3,-4,0);
    char line11[] = "!! YOU HAVE ONLY 30 SECS !!";
    for(int i = 0; i < strlen(line11); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line11[i]);
    }
    glRasterPos3f(-5.5,-5,0);
    char line12[] = "!! You will lose IF THE SCORE BECOME NAGETIVE !!";
    for(int i = 0; i < strlen(line12); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line12[i]);
    }
    glColor3f(1,1,1);
    glRasterPos3f(-4,-7,0);
    char line13[] = "** Use <- and -> to control the catcher **";
    for(int i = 0; i < strlen(line13); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line13[i]);
    }
    glColor3f(1, 0, 0);
    glRasterPos3f(-4,-8,0);
    char line14[] = "** Press ENTER to start **";
    for(int i = 0; i < strlen(line14); ++i){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line14[i]);
    }
    glutSwapBuffers();
}
//game display
void display(void){
    // cout << "in!" << endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glutSpecialFunc(catcher_move_func);
    coin();
    coinrepeat();
    coin2();
    star();
    catcher();
    stone();
    display_score();
    display_remain_time();
    glutSwapBuffers();
}
//
void keys(unsigned char key, int x, int y){
    if (key == 27){
        exit(0);
    }
    else if(key == 13){
        glutDisplayFunc(display);
        tStart = clock();
        entergame = true;
        score = 0;
        firstwindisplay = true;
    }
    
    glutPostRedisplay();
}

//win and lose display definition
void winDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(firstwindisplay){
        bool newrecord = false;
        readfile.open("record/record.txt", ios::in);
        if (readfile.is_open())
        {
            while(readfile >> record){
                if (record < score){
                    newrecord = true;
                    // cout << "new!";
                }
            }
            
        }
        else cout << "Unable to open file";
        
        // cout << record << endl;
        readfile.close();
        writefile.open("record/record.txt", ios::out);
        if (writefile.is_open())
        {
            if(newrecord) writefile << score;
            else writefile << record;
        }
        else cout << "Unable to open file";
        writefile.close();
    }
    firstwindisplay = false;

    glColor3f(1,1,0);
    glRasterPos3f(-8,0,0);
    char msg1[] = "----------Time's up!!!--------";
    for(int i = 0; i < strlen(msg1); ++i){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
    }
    glColor3f(1, 1, 1);
    glRasterPos2i(-2, -2);
    char buf[256];
    sprintf(buf, "Score: %d", score);
    for(int i = 0; i < strlen(buf); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
    }
    glColor3f(1,0,0);
    glRasterPos3f(-3.5,-3,0);
    if(record < score){
        char msg10[] = "!!! NEW RECORD !!!";
        for(int i = 0; i < strlen(msg10); ++i){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg10[i]);
        }
    }
    else{
        glColor3f(1,1,1);
        char record_buf[256];
        sprintf(record_buf, "--- Record: %d ---", record);
        for(int i = 0; i < strlen(record_buf); ++i){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, record_buf[i]);
        }
    }
    glColor3f(1,1,1);
    glRasterPos3f(-4,-7,0);
    char msg3[] = "Press ESC to QUIT......";
    for(int i = 0; i < strlen(msg3); ++i){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);
    }
    glRasterPos3f(-4,-8,0);
    char msg2[] = "Press ENTER to RESTART";
    for(int i = 0; i < strlen(msg2); ++i){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    }
    glutKeyboardFunc(keys);
    glutSwapBuffers();
}
void loseDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(firstlosedisplay){
        stringstream temp;
        temp << (double)((clock() - tStart)*10.0/CLOCKS_PER_SEC);
        temp >> output_time;
    }
    firstlosedisplay = false;
    glColor3f(1,0,0);
    glRasterPos3f(-8,0,0);
    char msg1[] = "----------YOU LOSE!!!--------";
    for(int i = 0; i < strlen(msg1); ++i){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
    }
    glColor3f(1, 1, 1);
    glRasterPos2i(-4, -2);
    char buf[256];
    sprintf(buf, "Score: %d", score);
    char msg4[] = "Time:";
    for(int i = 0; i < strlen(msg4); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg4[i]);
    }
    for (string::iterator i = output_time.begin(); i != output_time.end(); ++i)
    {
      char c = *i;
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    char msg5[] = "s   ";
    for(int i = 0; i < strlen(msg5); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg5[i]);
    }
    for(int i = 0; i < strlen(buf); ++i){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
    }
    glColor3f(1,1,1);
    glRasterPos3f(-4,-7,0);
    char msg3[] = "Press ESC to QUIT......";
    for(int i = 0; i < strlen(msg3); ++i){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);
    }
    glRasterPos3f(-4,-8,0);
    char msg2[] = "Press ENTER to RESTART";
    for(int i = 0; i < strlen(msg2); ++i){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    }
    glutSwapBuffers();
    glutKeyboardFunc(keys);
}

//control game objects' movements
void timer(int sec){
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    if(entergame){
        double time_duration = (double)(30.0-(clock() - tStart)*10.0/CLOCKS_PER_SEC);

        if(time_duration < 0){
            entergame = false;
            glutDisplayFunc(winDisplay);
        }
        if(score < 0){
            entergame = false;
            glutDisplayFunc(loseDisplay);
        }

        if(coin_y <= catcher_y+2 && !((coin_x+1 < catcher_x) || (coin_x > catcher_x+3))){
            coin_y = 9;
            coin_x = rand()%10+-10;
            score++;
            tStart2 = clock();
            
            
        }
        else if(coin_y <= -10){
            coin_y = 9;
            coin_x = rand()%10+-10;
        }
        else{
            coin_y-=0.20;
        }
        if(coinrepeat_y <= catcher_y+2 && !((coinrepeat_x+1 < catcher_x) || (coinrepeat_x > catcher_x+3))){
            coinrepeat_y = 9;
            coinrepeat_x = rand()%10;
            score++;
            tStart2 = clock();
        }
        else if(coinrepeat_y <= -10){
            coinrepeat_y = 9;
            coinrepeat_x = rand()%10;
        }
        else{
            coinrepeat_y-=0.20;
        }

        if(coin2_y <= catcher_y+2 && !((coin2_x+0.5 < catcher_x) || (coin2_x > catcher_x+3))){
            coin2_y = 9.5;
            coin2_x = rand()%20+-10;
            score+=2;
            tStart3 = clock();
        }
        else if(coin2_y <= -10){
            coin2_y = 9.5;
            coin2_x = rand()%20+-10;
        }
        else{
            coin2_y-=0.35;
        }

        if(star_y-0.4 <= catcher_y+2 && star_y+0.4 >= catcher_y+2 && !((star_x+0.6 < catcher_x) || (star_x > catcher_x+3))){
            star_y = 9.5;
            star_x = rand()%20+-10;
            score+=5;
            tStart4 = clock();
        }
        else if(star_y <= -10){
            star_x = rand()%18-9.4;
            star_y = 9.3;
        }
        else{
            star_y-=0.15;
            switch (star_goes_left)
            {
            case true:
                if (star_x-0.4 > -10)
                    star_x-=0.25;
                else    
                    star_goes_left = false;
                break;
            
            default:
                if(star_x + 0.4 < 10)
                    star_x+=0.25;
                else    
                    star_goes_left = true;
                break;
            }
        }
        if(stone_y <= catcher_y+2 && !((stone_x+1 < catcher_x) || (stone_x > catcher_x+3))){
            stone_y = 9;
            stone_x = rand()%20+-10;
            score-=3;
            tStart5 = clock();
        }
        else if(stone_y <= -10){
            stone_y = 9;
            stone_x = rand()%20+-10;
        }
        else{
            stone_y-=0.20;
        }
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Coin Catcher");
    
    glutDisplayFunc(welcomeDisplay);  
    glutKeyboardFunc(keys); 
    glutReshapeFunc(catcher_reshape);
    glutReshapeFunc(coin_reshape);
    glutReshapeFunc(coin2_reshape);
    glutReshapeFunc(stone_reshape);
    glutTimerFunc(0, timer, 0);
    score = 0;
    glutMainLoop();
    return 0;
}