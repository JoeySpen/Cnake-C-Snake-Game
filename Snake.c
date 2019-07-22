//gcc snake.c -lncurses
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct player{
  int xPos;
  int yPos;
  int xDir;
  int yDir;
  player * next;
}player;

//Initialises ncurses window
void windowSetup(){
  initscr();
  noecho();
  refresh();
  curs_set(0);
  nodelay(stdscr, true);
  return;
}

//Draws dots to the screen, called first and is then overwritten by the snake
void drawScreen(){
  for(int i = 0; i < 10; i++){
    mvprintw(i, 0, "............");
  }
  return;
}

void snakeUpdate(player * s){
  s->xPos = s->xPos + s->xDir;
  s->yPos = s->yPos + s->yDir; 
}

void snakeDraw(player * s){
  mvprintw(s->yPos, s->xPos, "X");
}

//Gets the players input
void getInput(char input, player * s){
  switch (input){
    case 'q':
      endwin();
      exit(0);
      break;
    
    case 'w':
      s->yDir = -1;
      s->xDir = 0;
      break;

    case 'a':
      s->yDir = 0;
      s->xDir = -1;
      break;

    case 's':
      s->yDir = 1;
      s->xDir = 0;
      break;

    case 'd':
      s->yDir = 0;
      s->xDir = 1;
      break;

    default:
      break;
  }
}

//Main method
int main(){
  windowSetup();

  //Create the snake
  player * snake = malloc(sizeof(player));

  snake->xPos = 0;
  snake->yPos = 0;
  snake->xDir = 0;
  snake->yDir = 1;

  //Main game loop
  while(1){
    drawScreen();

    getInput(getch(), snake);
    snakeUpdate(snake);
    snakeDraw(snake);


    //Draws the screen
    refresh();
    napms(250);
  }
}