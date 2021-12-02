#include<windows.h>
#include<w32api.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include "game.h"
#include<string>

#define ROWS 40.0
#define COLUMNS 40.0

std::ofstream ofile;
std::ifstream ifile;
bool game_over=false;
extern int sDirection;
int score=0;
int fps=5;
void init();
void display_callback();
void input_callback(int,int,int);
void reshape_callback(int,int);
void timer_callback(int);

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(600,600);
    glutCreateWindow("SNAKE Xenzia");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(input_callback);
    glutTimerFunc(1000/fps,timer_callback,0);
    init();
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    initGrid(COLUMNS,ROWS);
}

//Callbacks
void display_callback()
{
    if(game_over)
    {
        ofile.open("score.dat",std::ios::trunc);
        ofile<<score<<std::endl;
        ofile.close();
        ifile.open("score.dat",std::ios::in);
        char a[4];
        ifile>>a;
        //std::cout<<a;
        char text[50]= "Your score : ";
        strcat(text,a);
        MessageBox(NULL,text,"Game Over",0);
        exit(0);
    }
    //glColor3f(1.0,0.0,0.0);
    if (level==1)
    glClearColor(0.906,0.742,0.671,0.0);
    if (level==2||level==4)
    glClearColor(0.0,0.0,0.0,0.0);
    if (level==3)
    glClearColor(1.0,0.0,0.0,0.0);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    draw_grid();
    draw_food();
    draw_snake();
    glutSwapBuffers();
}
void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLfloat)w,GLfloat(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/fps,timer_callback,0);
    //glutTimerFunc(10,timer_callback,0);
}//timer
void input_callback(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
            sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }
}
//all user input i.e. key pressed interaction
