//
// Created by Ethan Escalante on 4/28/24.
//

#ifndef CS315_PROJECT5_SP24_WORM_HPP
#define CS315_PROJECT5_SP24_WORM_HPP

#include <queue>
class Worm {

  /*
    addHead  // given a cell, adds it to the queue to represent the new head of the queue
    removeTail // removes the element that has been in the queue the longest.
    head // return the cell that represents the head element of the queue
    tail // return the cell that represents the tail element of the queue
    */
public:
    Worm(int rowC, int colC);
    void addHead(int row, int col);
    void removeTail();
    std::pair<int,int> head();
    std::pair<int,int> tail();
    int numElementsInQueue();
    Worm nextHeadPosition(char c);
    std::queue< std::pair<int, int> > wormQueue;
    std::vector< std::pair<int, int> > wormCircularQueue;



    // initially, use STL's queue class.
    // Once you finish your project,
    // change the implementation to a circular queue.
private:

    int rows;
    int cols;

    int maxSize;
    int headIndex;
    int tailIndex;






};


#endif //CS315_PROJECT5_SP24_WORM_HPP
