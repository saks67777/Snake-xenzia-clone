#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define MAX 7
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2
#define FPS 10
extern int fps;
extern int level;
//global int fps=5;

void initGrid(int,int);
void draw_grid();
void draw_food();
void draw_snake();

#endif // GAME_H_INCLUDED
