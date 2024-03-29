//gcc snake.c -lncurses
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define HEIGHT 20
#define WIDTH 40

int score = 0;

typedef struct player{
  int xPos;
  int yPos;
  int xDir;
  int yDir;
  struct player * next;
  struct player * prev;
}player;

typedef struct fruit{
  int xPos;
  int yPos;
}fruit;

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
  for(int i = 2; i < HEIGHT; i++){
    for(int j = 1; j < WIDTH; j++)
      mvprintw(i, j, ".");
  }
  return;
}

void drawScore(){
  mvprintw(0, 0, "Score: %d   " , score);
}

//Updates the position of all parts of the snake
void snakeUpdate(player * s){
  //Go to the last part of the snake
  while(s->next != NULL){
    s = s->next;
  }
  
  //Work back applying values
  while(s->prev != NULL){
    s->xPos = s->prev->xPos;
    s->yPos = s->prev->yPos;
    s = s->prev;
  }

  //Updates the head
  s->xPos = s->xPos + s->xDir;
  s->yPos = s->yPos + s->yDir;
}

//Draws the snake
void snakeDraw(player * s){
  while(s != NULL){
    mvprintw(s->yPos, s->xPos, "X");
    s = s->next;
  }
}

//Adds another character to the snake
void snakeAdd(player * s){
  while(s->next != NULL){ //Finds the end of the snake
    s = s->next;
  }
  s->next = malloc(sizeof(player));
  s->next->xPos = s->xPos + (-1* s->xDir);
  s->next->yPos = s->yPos + (-1* s->yDir);
  s->next->xDir = s->xDir;
  s->next->yDir = s->yDir;
  s->next->next = NULL;
  s->next->prev = s;
}

//Prints some information about the location of the snake
void snakePosDebug(player * s){
  int i = 0;
  while(s != NULL){
    mvprintw((15+i),15,"Snake %d, xPos: %d, yPos: %d " ,i, s->xPos, s->yPos);
    i++;
    s = s->next;
  }
}

//Removes the fruit
void fruitEat(fruit * f){

}

//Places the fruit randomly
void fruitAdd(fruit * f){
  mvprintw(f->yPos, f->xPos, ".");
  f->yPos = (rand()%HEIGHT) + 2; // + 2 prevents fruit appearing in border
  f->xPos = rand()%WIDTH;
  mvprintw(f->yPos, f->xPos, "F");
}

void fruitDraw(fruit * f){
  mvprintw(f->yPos, f->xPos, "F");
}

//Checks the character the snake has just entered
void snakeCheck(player * s, fruit * f){
  char check = mvinch(s->yPos, s->xPos);
  mvprintw(10,25, "check:%c" ,check);
  switch(check){
    case 'X':
      endwin();
      exit(0);
      break;
    
    case 'F':
      fruitAdd(f);
      snakeAdd(s);
      score++;
      drawScore();
      break;

    default:
      break;
  }
}

//Gets the players input
void getInput(char input, player * s){
  switch (input){
    case 'q':
      endwin();
      exit(0);
      break;
    
    case 'w':
      if(s->yDir != 1){
        s->yDir = -1;
        s->xDir = 0;
      }
      break;

    case 'a':
      if(s->xDir != 1){
        s->yDir = 0;
        s->xDir = -1;
      }
      break;

    case 's':
      if(s->yDir != -1){
        s->yDir = 1;
        s->xDir = 0;
      }
      break;

    case 'd':
      if(s->xDir != -1){
        s->yDir = 0;
        s->xDir = 1;
      }
      break;

    default:
      break;
  }
}

void drawBox(int h, int w){
  mvhline(1, 0, 'A', w);
  mvhline(h, 0, 'A', w);
  mvvline(1, 0, 'A', h);
  mvvline(1, w, 'A' , h);
}

//Main method
int main(){
  windowSetup();
  drawScore();

  //Create the snake
  player * snake = malloc(sizeof(player));
  fruit * fruit = malloc(sizeof(fruit));
  fruit->yPos = 2;
  fruit->xPos = 1;

  snake->xPos = 5;
  snake->yPos = 5;
  snake->xDir = 0;
  snake->yDir = 1;
  snake->prev = NULL;

  drawBox(HEIGHT, WIDTH);
  
  for(int i = 0; i<2; i++){
    snakeAdd(snake);
  }
  fruitAdd(fruit);

  //Main game loop
  while(1){
    getInput(getch(), snake);
    snakeUpdate(snake);
    snakeCheck(snake, fruit);  
    drawScreen(); 
    fruitDraw(fruit);
    snakeDraw(snake); 

    //snakePosDebug(snake);

    //Draws the screen
    refresh();
    napms(250);
  }
}