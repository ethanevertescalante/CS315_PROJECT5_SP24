#include<curses.h>
#include<iostream>
#include "getChar.hpp"
#include "ScreenDS.hpp"
#include "Worm.hpp"

//helper functions creation
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



    //Telling user about arguments
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

    //screen object
    ScreenDS SDS(row, col);

    //variable creation/assignment
    int centerRow = (row+2)/2;
    int centerCol = col/2;
    int score = 0;



    startup();

    //Info Text
    move(0,0);
    addstr("Ethan Snake Game CS315 SP24");
    move(1, 0);
    addstr("Score: ");

    //Initializing Score
    std::string scoreString = std::to_string(score);
    char const *scoreScreen = scoreString.c_str();
    move(1, 8);
    addstr(scoreScreen);
    drawPlayArea(row, col, SDS);


    //worm starting position and initialize on board
    Worm worm(centerRow, centerCol);
    worm.addHead(centerRow, centerCol);
    move(centerRow, centerCol);
    SDS.mkOccupied(centerRow, centerCol);

/*

    for (int i = 2; i < row + 2; i++) {
        move(i, 0);
        for (int j = 0; j < col; j++) {
            move(i, j);
            if (SDS.isFree(i, j)) {
                addstr("1");
            } else if(!SDS.isFree(i,j)){
                addstr("0");
            }
        }
    }

*/




    //Creating/Initializing Game Loop Variables
    bool isWormAlive = true;
    int nextRow = centerRow;
    int nextCol = centerCol;
    std::pair<int, int> temp = SDS.getARandomCell();
    int nextMunchie = getNextMunchie(temp,SDS);
    bool addTails = false;
    int tailCounter = 0;
    int lastMunchie = 0;



    //driving code loop
    while(isWormAlive) {
        //loop variables that will reset with each iteration of a loop
        int prevRow = nextRow;
        int prevCol = nextCol;
        char c = getChar();
        char last;

        move(prevRow, prevCol);
        SDS.mkFree(prevRow, prevCol);
        //SDS.updateFreepool(prevRow, prevCol);
        addstr("o");

        //moving directions
        if (c == 'w' || c == 'k') {
            nextRow--;
            last = 'w';
        } else if (c == 's' || c == 'j') {
            nextRow++;
            last = 's';
        } else if (c == 'a' || c == 'h') {
            nextCol--;
            last = 'a';
        } else if (c == 'd' || c == 'l') {
            nextCol++;
            last = 'd';
        } else {
            //this is if a user presses a non-valid key, the last valid press will be taken instead
            if (last == 'w') {
                nextRow--;
            } else if (last == 's') {
                nextRow++;
            } else if (last == 'a') {
                nextCol--;
            } else if (last == 'd') {
                nextCol++;
            }

        }

        //check to see if tail is growing
        if (addTails) {
            move(prevRow, prevCol);
            SDS.mkOccupied(prevRow, prevCol);
            //SDS.updateFreepool(prevRow, prevCol);
            worm.addHead(prevRow, prevCol);
            addstr("o");
            tailCounter++;
        }

        //reset tailCounter if it finishes printing the number of tails needed
        if (tailCounter == lastMunchie) {
            addTails = false;
            tailCounter = 0;
        }



        //munchie logic
        if ((nextRow == temp.first) && (nextCol == temp.second)) {
            updateScore(score, nextMunchie);
            temp = SDS.getARandomCell();
            addTails = true;
            lastMunchie = nextMunchie;
            nextMunchie = getNextMunchie(temp, SDS);

        }


        //std::cout << "[" << nextRow << "," << nextCol << "]\n";


        //TODO:: need to implement the queue and keep track of where the head and tail are

        //check if snake is still alive
        if (!(SDS.isFree(nextRow, nextCol))) {
            isWormAlive = false;
        } else if (!addTails) {


            //only dequeue if tail is not currently growing
            std::pair<int, int> tailPos = worm.tail();
            worm.removeTail();
            move(tailPos.first, tailPos.second);
            SDS.mkFree(tailPos.first, tailPos.second);
            //SDS.updateFreepool(tailPos.first, tailPos.second);
            addstr(" ");

            //enqueue
            move(nextRow, nextCol);
            SDS.mkOccupied(nextRow, nextCol);
            //SDS.updateFreepool(nextRow, nextCol);
            worm.addHead(nextRow, nextCol);
            move(nextRow, nextCol);
            addstr("@");

            if (worm.numElementsInQueue() != 1) {
                move(prevRow, prevCol);
                SDS.mkOccupied(prevRow, prevCol);
                //SDS.updateFreepool(prevRow, prevCol);
                addstr("o");
            }


        } else {
            //enqueue regardless
            move(nextRow, nextCol);
            SDS.mkOccupied(nextRow, nextCol);
            //worm.addHead(nextRow, nextCol); //can not do this in this stage, but we still have to update the placement of the head
            worm.head() = std::make_pair(nextRow, nextCol);
            move(nextRow, nextCol);
            addstr("@");

        }


        refresh(); //for screen to update

    }

    terminate();

    bool debug = false;
 if(debug) {
     //debug values
     std::cout << "\n";
     std::cout << "*************DEBUG******************\n";
     std::cout << "Head Cord: " << worm.head().first << " " << worm.head().second << std::endl;
     std::cout << "Tail Cord: " << worm.tail().first << " " << worm.tail().second << std::endl;
     std::cout << "Num Elements in Queue: " << worm.numElementsInQueue() << std::endl;
     std::cout << "Freepool Size: " << SDS.sizeOfFreepool() << std::endl;
     std::cout << "*************DEBUG******************\n";
     std::cout << "\n";
 }
    //terminating output
    std::cout << "The worm crashed into something and DIED!!\n";
    std::cout << "Final Score: " << score << std::endl;



}

//helper functions fully implemented
void drawPlayArea( int row, int col, ScreenDS SDS ){

  //draw and set free and occupied cells Initially
  for (int i = 2; i < row + 2; i++) {
    move(i, 0);
    for (int j = 0; j < col; j++) {
        if (i == 2 || i == row + 1 || j == col - 1 || j == 0) {
            move(i, j);
            SDS.mkOccupied(i, j);
            addstr("*");
            //std::cout << "-1";
        } else {
            SDS.mkFree(i, j);
            //std::cout << SDS.screen[i][j];
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
    //int munchInt = 1; //for testing
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