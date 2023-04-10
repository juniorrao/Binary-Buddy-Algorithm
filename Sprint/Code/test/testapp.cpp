/************************************************************************************
**
**        DESCRIPTION    :    Group-6(Binary Buddy Algorithm )
**
**       last updated    :    09-04-2023
**
**
************************************************************************************/

#include "../inc/binary.h" //include the binary buddy library 
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>



using namespace std;
using namespace binary; // all functions are written in binary namespace in binary buddy library


int main()
{

    Binary algo; // creates an object of the library to perform and test certain operations on it

    bool start  = true; // variable to start the loop for menu
    while(start)
    {
        int input; // user input is stored in it
        cout <<"\n Press: [1] Allocate  [2] Deallocate  [3] Exit -> ";
        cin >> input;
        var value = 0;
        switch (input)
        {
        case 1:
            cout <<"\n Enter the amount of memory to allocate (= Block Value): ";
            cin >> value;
            if(value == 0)
            {
                cout <<"\n Error: Zero(0) cannot be allocated"<< endl;
		start = false;
                break;
            }
            if(!algo.allocate(value)) //call to allocate function of the binary buddy library to allocate the memory.
            {

                cout <<"\n Error: Memory insufficient or space is not available"<< endl;
		start = false;
                break;

            }
            cout <<"\n THE BLOCKS IN MEMORY\n" << endl;
            algo. display(); // after allocating we need to display the current status of memory, so display is called.
            break;
        case 2:
            cout <<"\n Enter the start address of block to deallocate (Start): ";
            cin >> value;
            if(!algo.deallocate(value)) // call to deallocate function of the binary buddy library to deallocate the memory.
            {
                cout <<"\n Error: Block is not allocated at given address"<< endl;
		start = false;
                break;
            }
            cout <<"\n THE BLOCKS IN MEMORY\n" << endl;
            algo.display(); // after deallocating we need to display the status of memory, so display is called.
            break;
        case 3:
            cout <<"\n Program terminated\n"<< endl; //user wants to exit // break out of switch and come out of loop 
            start = false;
            break;

        default:
            cout <<"\n Error: Invalid input"<< endl;
	    start = false;
        }
    }

    return 0;
}
