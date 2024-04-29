//
// Created by Ethan Escalante on 4/27/24.
//

#ifndef CS315_PROJECT5_SP24_SCREENDS_HPP
#define CS315_PROJECT5_SP24_SCREENDS_HPP
#include <vector>
#include "curses.h"

class ScreenDS {



public:
    // functions
    ScreenDS(int row, int col);
    void mkFree(int row, int col);
    bool isFree(int row, int col);
    void mkOccupied(int row, int col);
    std::pair<int, int> getARandomCell();
    int sizeOfFreepool();
    int getMunchie();
    std::vector< std::vector<int> > screen;
    std::vector<int> freepool;
    /*
    mkFree  -- given a cell, make it to be a free cell
    mkOccupied -- given a free cell, make it so that it no longer is free, it is a cell that belongs to the worm
    isFree -- given a cell, determine if it is free or not
    getARandomCell -- randomly selects and returns a free cell to represents a munchie
    */
private:
    //helper functions
    void mkFreeHelper(int row, int col, int* indexOfFreepool);



    // freepool (a 1D vector) and screen (a 2D vector)
    // initialize the internal representation of the screen in the constructor


    int rows;
    int cols;
    int lastIndexOfFreepool;



};


#endif //CS315_PROJECT5_SP24_SCREENDS_HPP
