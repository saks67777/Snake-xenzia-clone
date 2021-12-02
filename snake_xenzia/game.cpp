#include<windows.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include "game.h"
#include<w32api.h>
#include <fstream>

#include<string>

std::ofstream ofile1;
std::ifstream ifile2;

void unit(int,int);
int random(int,int);
int level=1;
bool length_inc=false;
bool seedflag = false;
extern int score;
extern bool game_over;
bool food=false;
int rows=0,columns=0;
int sDirection = RIGHT;
int foodx,foody;
int posx[MAX+1]={4,3,2,1,0,-1,-1};
int posy[MAX+1]={10,10,10,10,10,10,10};
int length=7;

//The previous 3 lines initialize the snake position

void initGrid(int x,int y)
{
    columns=x;
    rows=y;
}
//initializes grid
void draw_grid()
{
    for(int i =0;i<columns;i++)
    {
        for(int j=0;j<rows;j++)
            {unit(i,j);}
    }
        if (level==2||level==4)
    {
        for(int x=0;x<columns;x++)
        {

        for (int y=0;y<rows;y++)
        {


        if(((x==10||x==30)&&y>=15&&y<=25)||(((y==10||y==30)&&x>=15&&x<=25)))
        {
            glColor3f(1.0,0.0,1.0);
            glBegin(GL_LINES);
        glVertex2d(x,y); glVertex2d(x+1,y);
        glVertex2d(x+1,y); glVertex2d(x+1,y+1);
        glVertex2d(x+1,y+1); glVertex2d(x,y+1);
        glVertex2d(x,y+1); glVertex2d(x,y);
        glEnd();
        }
        }
        }
}}
//uses unit[i,j] to draw each individual square of the grid
void draw_snake()
{
    for(int i =length-1;i>0;i--)
    {
        posx[i]=posx[i-1];
        posy[i]=posy[i-1];
    }
    //this is to say that the previous parts of the body will take old position of next part
    for(int i=0;i<length;i++)
    {
        if (level==1)
        glColor3f(1.0,0.0,1.0);
        if (level==2||level==3||level==4)
        glColor3f(1.0,0.0,0.0);
        if(i==0)
        {
            glColor3f(0.0,0.0,1.0);
            switch(sDirection)
            {
            case UP:
                posy[i]++;
                break;
            case DOWN:
                posy[i]--;
                break;
            case RIGHT:
                posx[i]++;
                break;
            case LEFT:
                posx[i]--;
                break;
            }
            //for the position of head
            if(posx[i]==0||posx[i]==columns-1||posy[i]==0||posy[i]==rows-1)

                game_over=true;
                //for collision with corner walls
                             if (level==2||level==4)
               {
                   for (int x=0;x<columns;x++)
                   {
              for (int y=0;y<rows;y++)
            {


      if(((x==10||x==30)&&y>=15&&y<=25)||(((y==10||y==30)&&x>=15&&x<=25)))
        {
                        if(posx[0]==x&&posy[0]==y)
            game_over=true;
        }
                   }}
         }
            if(posx[i]==foodx && posy[i]==foody)
            {
                food=false;
                score++;
                if(length<=MAX)
                    length_inc=true;
                if(length==MAX)
                {
                    if (level!=4)
                    {


                    length=5;
                    length_inc=false;


                      /*
                      char text1[50]= "You Win\nYou completeted level ";
                      strcat(text1,b);*/
                      //char b=level;

                       if (level==1)
                        MessageBox(NULL,"You completed level 1","Awesome",0);
                       if (level==2||level==4)
                         MessageBox(NULL,"You completed level 2","Awesome",0);
                        if (level==3)
                         MessageBox(NULL,"You completed level 3","Awesome",0);

                    fps=level*FPS;
                    level=level+1;
                    }
                    else
                    {
                        MessageBox(NULL,"You completed the game congrats","Awesome",0);
                        game_over=true;
                    }
                }
            }
            //for interaction with food
            for(int j=1;j<length;j++)
            {
                if(posx[j]==posx[0] && posy[j]==posy[0])
                    game_over=true;

            }
            //for game over when snake touches own body
        }
       //if(i!=0)
        //{


        glBegin(GL_QUADS);

            glVertex2d(posx[i],posy[i]); glVertex2d(posx[i]+1,posy[i]); glVertex2d(posx[i]+1,posy[i]+1); glVertex2d(posx[i],posy[i]+1);
        glEnd();
        //}
        //else
        //{
        //glBegin(GL_TRIANGLES);
        //glVertex2f(posx[i],posy[i]); glVertex2f(posx[i],posy[i]+1); glVertex2f(posx[i]+1,posy[i]+0.5);
        //}
    }
    if(length_inc)
    {
        length++;
        length_inc=false;
    }
}

void draw_food()
{
    if(!food)
    {
        foodx=random(2,columns-2);
        int tempy=random(2,rows-2);
        if (level==2||level==4)
        {
            if(((foodx==10||foodx==30)&&tempy>=15&&tempy<=25)||(((tempy==10||tempy==30)&&foodx>=15&&foodx<=25)))
                tempy=35;
        }
        foody=tempy;
        //std::cout<<foodx<<foody<<std::endl;
        food=true;
    }
    glBegin(GL_QUADS);
        if (level==1)
            glColor3f(0.0,1.0,0.0);
        if (level==2||level==4)
            glColor3f(1.0,0.0,1.0);
                glVertex2d(foodx,foody); glVertex2d(foodx+1,foody); glVertex2d(foodx+1,foody+1); glVertex2d(foodx,foody+1);
    glEnd();

}
//draws food
void unit(int x,int y)
{
    glLoadIdentity();
    if(x==0||x==columns-1||y==0||y==rows-1)
    {
        glLineWidth(4.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glColor3f(1.0,1.0,1.0);
        glLineWidth(1.0);
    }
    if (level==2||level==4)
    {
        if(((x==10||x==30)&&y>=15&&y<=25)||(((y==10||y==30)&&x>=15&&x<=25)))
        {
            glColor3f(1.0,0.0,1.0);
        }
    }
    glBegin(GL_LINES);
        glVertex2d(x,y); glVertex2d(x+1,y);
        glVertex2d(x+1,y); glVertex2d(x+1,y+1);
        glVertex2d(x+1,y+1); glVertex2d(x,y+1);
        glVertex2d(x,y+1); glVertex2d(x,y);
        //glVertex2d(x,y); glVertex2d(x+1,y);
        //glVertex2d(x+1,y); glVertex2d(x+1,y+1);
    glEnd();

    }

//draws each grid square
int random(int _min,int _max)
{
    if(!seedflag)
    {
        srand(time(NULL));
        seedflag=true;
    }
    else
        seedflag=false;
    int new12= _min+rand()%(_max-_min);

    return new12;
}

