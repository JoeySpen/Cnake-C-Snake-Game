//gcc snake.c -lncurses
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct snake{
  int xPos;
  int yPos;
}snake;

//Initialises ncurses window
void windowSetup(){
  initscr();
  noecho();
  refresh();
  curs_set(0);
  nodelay(stdscr, true);
  return;
}

//Draws dots to the screen
void drawScreen(){
  for(int i = 0; i < 10; i++){
    mvprintw(i, 0, "............");
  }
  return;
}

//Gets the players input
void getInput(char input){
  switch (input){
    case 'q':
      endwin();
      exit(0);
  }
}

//Main method
int main(){
  windowSetup();

  //Main game loop
  while(1){
    getInput(getch());
    drawScreen();
    refresh();
  }
}