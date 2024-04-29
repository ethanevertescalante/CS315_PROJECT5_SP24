#include<curses.h>
#include<iostream>
#include "getChar.hpp"
#include "ScreenDS.hpp"
#include "Worm.hpp"

void startup( void );
void terminate( void );
void drawPlayArea( int row, int col, ScreenDS SDS );
void handleMovement( char c );
int getNextMunchie(std::pair<int, int>,ScreenDS SDS);
void updateScore(int& score1, int score2);

int main(int argc, const char *argv[])
{
  // For this project, you only need to learn a handful of curses functions.
  // They are:

  // move(int x, int y) -- moves the cursor to (x, y). The top-left cell on the
  //                  screen is at (0, 0)

  // addstr(char *str) -- add the C string, str, to the screen at the current location of 
  //                     the cursor. note that the argument to this function is a C string,
  //                     not a C++ string. 

  // addch(char c) -- add c to the screen at the current position of the cursor.

  // mvaddch(int x, int y, char c) -- add c at (x, y)

  // refresh() -- the changes that you make to the screen will only get displayed
  //              when you use this function to refresh the screen.

    if( argc != 3 ) {
      std::cout << "usage: " << argv[0] << " numRow(9-25) numCol(9-80) ";
      exit(1);
    }

    //Checking Arguments Before Moving On
    bool argumentError = false;
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);

    if( row < 9 || row > 25 ){
        argumentError = true;
        std::cout << "First Argument: Please Enter a Number between 9 and 25\n";
    }

    if(col < 9 || col > 80){
      argumentError = true;
      std::cout << "Second Argument: Please Enter a Number between 9 and 80\n";
    }

    if(argumentError){
      exit(2);
    }

    Worm worm(row, col);
    ScreenDS SDS(row, col);


    int centerRow = (row+2)/2;
    int centerCol = col/2;
    int score = 0;


    startup();

    move(0,0);
    addstr("Ethan Snake Game CS315 SP24");



    move(1, 0);
    addstr("Score: ");

    std::string scoreString = std::to_string(score);
    char const *scoreScreen = scoreString.c_str();
    move(1, 8);
    addstr(scoreScreen);
    drawPlayArea(row, col, SDS);

/*
    for (int i = 2; i < row + 2; i++) {
        move(i, 0);
        for (int j = 0; j < col; j++) {
            move(i, j);
            if (SDS.isFree(i, j)) {
                SDS.mkFree(i, j);
                //addstr("1");
            } else{
                SDS.mkOccupied(i, j);
                //addstr("0");
            }
        }
    }
*/
    //worm testing: starting position
    worm.addHead(centerRow, centerCol);
    move(centerRow, centerCol);
    SDS.mkOccupied(centerRow, centerCol);
    addch('@');
/*
    std::pair<int, int> temp = SDS.getARandomCell();

    //munchie infomation
    int munchInt = SDS.getMunchie();
    std::string munchString = std::to_string(munchInt);
    char const *munchScreen = munchString.c_str();
    move(temp.first,temp.second);
    addstr(munchScreen);
*/
    bool isWormAlive = true;
    int nextRow = centerRow;
    int nextCol = centerCol;


    std::pair<int, int> temp = SDS.getARandomCell();
    int nextMunchie = getNextMunchie(temp,SDS);

    //driving code loop
    while(isWormAlive){

        char c  = getChar();

        move(nextRow, nextCol);
        addstr(" ");
        //refresh();

        //legal inputs
        if(getChar() == 'w' || c == 'k'){
            nextRow--;
        }else if(c == 's' || c == 'j'){
            nextRow++;
        }else if(c == 'a' || c == 'h'){
            nextCol--;
        }else if(c == 'd' || c == 'l'){
            nextCol++;
        }

        //std::cout << "[" << nextRow << "," << nextCol << "]\n";

        //snake is on top of munchie
        //TODO:: need to implement the queue and keep track of where the head and tail are
        if((nextRow == temp.first) && (nextCol == temp.second)){
            updateScore(score, nextMunchie);
            temp = SDS.getARandomCell();
            nextMunchie = getNextMunchie(temp, SDS);

        }

        //check if snake is still alive
        if(!(SDS.isFree(nextRow, nextCol)) ){
            isWormAlive = false;
        }else{
            //move @ and refresh screen to mimic movement
            move(nextRow, nextCol);
            addstr("@");
        }

        refresh();

    }

    terminate();


    std::cout << "The worm crashed into something and DIED!!\n";
    std::cout << "Final Score: " << score << std::endl;
/*
    //testing
    for (int i = 2; i < row + 2; i++) {
        for (int j = 0; j < col; j++) {
                std::cout << SDS.screen[i][j] << ' ';

        }
        std::cout << std::endl;
    }

    std::cout << SDS.sizeOfFreepool() << std::endl;
    std::cout << temp.first << ' ' << temp.second  <<std::endl;
    std::cout << munchInt << std::endl;

*/
}


void drawPlayArea( int row, int col, ScreenDS SDS ){

  //draw and set free and occupied cells
  for (int i = 2; i < row + 2; i++) {
    move(i, 0);
    for (int j = 0; j < col; j++) {
        if (i == 2 || i == row + 1 || j == col - 1 || j == 0) {
            move(i, j);
            SDS.mkOccupied(i, j);
            addstr("*");
        }else{
            SDS.mkFree(i, j);
        }
    }

  }

}


void startup( void )
{
     initscr();	 /* activate the curses */
     curs_set(0);/* do not display the cursor */
     clear();	 /* clear the screen that curses provides */
     noecho();	 /* prevent the input chars to be echoed to the screen */
     cbreak();	 /* change the stty so that characters are delivered to the
		    program as they are typed--no need to hit the return key!*/
}

void terminate( void )
{
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     clear();
     refresh();
     endwin();
}

int getNextMunchie(std::pair<int, int> temp, ScreenDS SDS){
    int munchInt = SDS.getMunchie();

    std::string munchString = std::to_string(munchInt);
    char const *munchScreen = munchString.c_str();

    move(temp.first,temp.second);
    addstr(munchScreen);

    return munchInt;

}

void updateScore(int& score1,int score2){
    score1+=score2;
    std::string scoreString = std::to_string(score1);
    char const *scoreScreen = scoreString.c_str();
    move(1, 8);
    addstr(scoreScreen);

}