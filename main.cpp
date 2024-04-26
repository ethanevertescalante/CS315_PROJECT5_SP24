#include<curses.h>
#include<iostream>
#include "getChar.hpp"

void startup( void );
void terminate( void );

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




     startup();


    move(1, 0);  // move the cursor to the top- and left-most block.
    addstr("0123456789012345678901234567890123456789");
    addstr("0123456789012345678901234567890123456789");

    move(1, 0);  // move the cursor to the second row, first column.
    addch('*');  // put a character at (1, 0)





     move(1, 20);
     addstr( "This string starts on column 21.");

     mvaddch(1, 79, '*'); // same as: move(1, 79); addch('*');

     mvaddch(22, 0, '*');

     move(12, 30);
     addstr( "ooooooo@");

     mvaddch(22, 79, '*');
     refresh();  // this function call forces the screen to be updated.
     //the following function moves the cursor to (4, 5) and then
     //writes a string.  It is equivalent to the following two stmts:
     move(4, 5);
     addstr("Type in a non-blank character, after it is echoed ");
     mvaddstr(4, 5, "Type in a couple of non-blank characters ");
     addstr("and then wait and watch!");
     refresh();

     for(int i = 1; i < 15; i++) {
	  mvaddch( i + 5, i + 20, getChar() );
	  refresh();
     }	  
     terminate();
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
