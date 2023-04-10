#ifndef BINARYNODE_H_INCLUDED
#define BINARYNODE_H_INCLUDED
#include <iostream>
#include <cstdlib>

namespace bn {

    typedef size_t var;

    class BinaryNode { // Binary Node class is just the represntaion of a block in memory , Used by Binary Class to implement the library

    public:
        var space, value; // variables to store the size of block i.e. space and the actual space occupied i.e. user requested . i.e. value
        void *start_ptr = NULL; // a pointer pointing to the starting point of the block
        void *end_ptr = NULL; // a pointer pointing to the end point of the block
        bool allocated; // a boolean variable to check if a block is allocated to user or not.
        var startAddress, endAddress; // start address and end address in human readable form for user input
        BinaryNode(var space): space(space), value(0), allocated(false) {}
        BinaryNode(var space, var value): space(space), value(value), allocated(true) {}


    };


}



#endif // BINARYNODE_H_INCLUDED
