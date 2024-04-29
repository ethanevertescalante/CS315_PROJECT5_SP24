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
    Worm(int row, int col);
    void addHead(int row, int col);
    void removeTail();
    void head();
    void tail();
    int numElementsInQueue();




    // initially, use STL's queue class.
    // Once you finish your project,
    // change the implementation to a circular queue.
private:
    std::queue< std::pair<int, int> > wormQueue;
    int rows;
    int cols;


};


#endif //CS315_PROJECT5_SP24_WORM_HPP
