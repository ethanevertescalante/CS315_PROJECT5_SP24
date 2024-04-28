//
// Created by Ethan Escalante on 4/27/24.
//
#include <iostream>
#include "ScreenDS.hpp"

ScreenDS::ScreenDS(int row, int col):rows(row), cols(row),screen(row,std::vector<int>(col,0)), freepool(row*col, 0), lastIndexOfFreepool(0){}

int ScreenDS::sizeOfFreepool() {
    return freepool.size();
}

bool ScreenDS::isFree(int row, int col){
    return mvinch(row, col) != '*' || mvinch(row, col) != '@' || mvinch(row, col) != 'o';
}

void ScreenDS::mkFree(int row, int col) {
    screen[rows][cols] = lastIndexOfFreepool;
    lastIndexOfFreepool++;
}

void ScreenDS::mkOccupied(int row, int col) {
    screen[rows][cols] = -1;
}

