//
// Created by Ethan Escalante on 4/28/24.
//

#include "Worm.hpp"
Worm::Worm(int row, int col): rows(row), cols(col) {}


void Worm::addHead(int row, int col) {
    wormQueue.push(std::make_pair(row, col));
}

void Worm::removeTail() {

}

int Worm::numElementsInQueue() {
    return wormQueue.size();
}

