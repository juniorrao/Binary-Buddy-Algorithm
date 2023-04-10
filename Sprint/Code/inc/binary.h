
//Header Guard

#ifndef BINARY_H_INCLUDED
#define BINARY_H_INCLUDED


//Including all the user defined header files
#include "binaryNode.h"

#include "config.h"

#include "log.h"
#include <string>
#include <vector>



//using namespace level
using namespace bn;
using namespace config;
using namespace logger;
using namespace std;

namespace binary {


  class Binary {					//Defining the Binary class
    
	void * mainMemory = NULL;		//Initially mainMemory set to NULL
    var MEMORY;

    vector < BinaryNode * > container;		//Declaring pointer node type vector 
    Config settings;		//Creating object of Config class
    Logger logger;			////Creating object of Logger class

    public:



	//Prototyping all the needed methods
	
    var give_fitter(var);

    vector < BinaryNode * > give_slots(var,var);

    Binary();
    bool is_power_of_two(var);
    string print_node(const BinaryNode *);
    bool allocate(var);
    bool buddies(BinaryNode * a, BinaryNode * b);	//passing two nodes as a parameter
    void check_merge();
    bool deallocate(var);
    void display();

	//Destructor Declaration
    ~Binary();

  };

}

#endif // BINARY_H_INCLUDED
