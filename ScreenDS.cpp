//
// Created by Ethan Escalante on 4/27/24.
//
#include <random>
#include <ctime>
#include "ScreenDS.hpp"

ScreenDS::ScreenDS(int row, int col):rows(row), cols(col),screen(row*col,std::vector<int>(col*row,0)), freepool(row*col, 0), lastIndexOfFreepool(0){}

int ScreenDS::sizeOfFreepool() {
    return lastIndexOfFreepool;
}

bool ScreenDS::isFree(int row, int col){
    return mvinch(row, col) != '*' && mvinch(row, col) != 'o';
}

void ScreenDS::mkFree(int row, int col) {
    screen[row][col] = lastIndexOfFreepool;
    freepool[lastIndexOfFreepool] = screen[row][col];
    lastIndexOfFreepool++;


}

void ScreenDS::mkOccupied(int row, int col) {
    screen[row][col] = -1;
}

std::pair<int, int> ScreenDS::getARandomCell() {

    srand(time(nullptr));

    int minRow = 3;
    int minCol = 1;
    int upRow = rows - 2;
    int upCol = cols - 2;

    int newRow = minRow + rand() % (upRow - minRow + 1);
    int newCol = minCol + rand() % (upCol - minCol + 1);

    return std::make_pair(newRow, newCol);


}

int ScreenDS::getMunchie() {
    int min = 1;
    int max = 9;

    int munchie = min + rand() % (max - min + 1);

    return munchie;

}