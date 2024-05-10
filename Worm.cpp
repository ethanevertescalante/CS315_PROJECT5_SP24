//
// Created by Ethan Escalante on 4/28/24.
//
#include <iostream>
#include<curses.h>
#include "Worm.hpp"
Worm::Worm(int rowC, int colC): wormCircularQueue((rowC-2)*(colC-2)), maxSize((rowC-2)*(colC-2)), headIndex(0), tailIndex(0) {
    //initial values :: max size is the freepool amount
    wormCircularQueue.reserve(maxSize);

}


void Worm::addHead(int row, int col) {
    //wormQueue.push(std::make_pair(row, col));
    //wormCircularQueue.push_back(std::make_pair(row, col));
    //if queue is full, we will need to resize
    if((headIndex + 1) % maxSize == tailIndex) {
        wormCircularQueue.reserve(maxSize*2);
    }
    wormCircularQueue[headIndex] = std::make_pair(row,col);
    headIndex = (headIndex + 1) % maxSize;
    if(headIndex == tailIndex){
        tailIndex = (tailIndex + 1) % maxSize;
    }
}

void Worm::removeTail() {
    //wormQueue.pop();
    tailIndex = (tailIndex + 1) % maxSize;
}

int Worm::numElementsInQueue() {
    //wormQueue.size();
    if(headIndex >= tailIndex){
        return headIndex - tailIndex;
    }
    return maxSize - (tailIndex - headIndex);

}

std::pair<int,int> Worm::head() {
    //return wormQueue.back();
    //std::cout << headIndex << std::endl;
    //return wormCircularQueue[headIndex];
    return wormCircularQueue[(headIndex - 1 + maxSize) % maxSize];
}

std::pair<int,int> Worm::tail(){
    //return wormQueue.front();
    return wormCircularQueue[tailIndex];
}

