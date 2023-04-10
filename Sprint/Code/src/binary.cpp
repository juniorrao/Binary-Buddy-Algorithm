/*****************************************************************************************
** 																					 	**
**																						**
**						DESCRIPTION		:	Sprint-6(Binary Buddy Algorithm)			**
**						Created By		: 	Team										**
**																						**
**                                                                                      **      
******************************************************************************************
*/
#include "../inc/binary.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>

const int KB = 1024;

using namespace bn;
using namespace binary;
using namespace logger;
using namespace std;

//Constructor Defination

Binary::Binary(): settings(), logger(settings.get_Log_Path()){

    MEMORY = settings.get_Pool_Size();
	
	
	//To check wheather total memory size is power of 2 or not
	//Also checking the upper limit i.e 2^32
	
    if(!is_power_of_two(MEMORY) || MEMORY> pow(2,32)){
	    stringstream error_message;
	   
	    error_message << "Invalid Memory Pool Size ( " << MEMORY << " ) :" ;
	    error_message << "Memory Pool Size of should be power of 2 and less than 2^32";
	    logger.write_log(error_message.str(), string("ERROR"));

	    exit(-1);
    }


    stringstream message;

    message << "Pool Memory: "<<MEMORY;
    string request_type = "Pool Allocation";
    
    //Writting the log request  to message stringstream
    
    logger.write_log(message.str(),request_type);

	//Pushing new node to the vector
	
    container.emplace_back(new BinaryNode(MEMORY));
    container[0]->startAddress = 0;
    container[0]->endAddress = container[0]->startAddress + container[0]->space;

    container[0]->start_ptr = malloc(container[0]->space*KB);
  	
	//typecast required as we can't do void pointer arithmatic
	
    container[0]->end_ptr = (void *)(((char*)container[0]->start_ptr) + container[0]->space);
    mainMemory = container[0]->start_ptr;


}

// checking given number is 2 raise or not

bool Binary::is_power_of_two(var n){
	if (n <= 0) {
        return false;
    }
    double log2n = log2(n);
    return floor(log2n) == log2n;
}

//Binary destructor defination

Binary::~Binary(){

    free(mainMemory);

}


//Definining the give_fitter method 

var Binary::give_fitter(var value)
{
    if(value == 1)
    {
        return 2;				//If user request 1 kb then we're returning 2kb
    }
    return pow(2, ceil( log(value) / log(2) ));
}


//give_slots() method defination

vector<BinaryNode*> Binary::give_slots(var space, var fitter)
{
    var number_of_slots = 2;
    if(space != fitter)				//If space and the fitter does not match
    {
        number_of_slots = 1 + ( log(space / fitter) / log(2) );
    }
    vector<BinaryNode*> v(number_of_slots, NULL);
    
	v[0] = new BinaryNode(fitter);			//Putting the request at the bottom of the vector i.e index 0
	
    for(var i = 1, s = fitter; i < number_of_slots; ++i, s *= 2)
    {
        v[i] = new BinaryNode(s);		
    }
    return v;		//Returning the vector 
}

/************************************************************************************
**
**
**               FUNCTION NAME 		:	allocate
**				 DESCRIPTION		:	Allocating the user request of memory
**				 RETURNS			:	Returns a boolean value
**				 CREATED BY			:	Team
**
**
*************************************************************************************
*/


bool Binary::allocate(var value)
{
    if(this->container.size() == 0)
    {
        return false;
    }


    var fitter = this->give_fitter(value);			//Calling the give_fitter() method that returns best fit block
    string request_type = "Allocation";

    for(var i = 0; i < container.size(); ++i)
    {
		//If the user request is same as 2 raise  and the block is unallocated
		
        if(container[i]->space == fitter && !container[i]->allocated)
        {
            container[i]->value = value;
            container[i]->allocated = true;
            container[i]->start_ptr = (void *)((char *)mainMemory + container[i]->startAddress);
            container[i]->end_ptr = (void *)((char *)mainMemory + container[i]->endAddress);
            logger.write_log(print_node(container[i]), request_type);
            return true;
        }
    }
    for(auto itr = container.begin(); itr != container.end(); ++itr)
    {
        BinaryNode *temp = *itr;
        if(!temp->allocated && temp->space > fitter)
        {
            auto slots = this->give_slots(temp->space, fitter);
            slots[0]->value = value;
            slots[0]->allocated = true;
            slots[0]->startAddress = temp->startAddress;
            slots[0]->endAddress = temp->startAddress + slots[0]->space;
            slots[0]->start_ptr = (void *)((char *)mainMemory + slots[0]->startAddress);
            slots[0]->end_ptr = (void *)((char *)mainMemory + slots[0]->endAddress);
            logger.write_log(print_node(slots[0]),request_type);
            for(var i = 1; i < slots.size(); ++i)
            {
                slots[i]->startAddress = slots[i-1]->endAddress;
                slots[i]->endAddress = slots[i]->startAddress + slots[i]->space;
                slots[i]->start_ptr = (void *)((char *)mainMemory + slots[i]->startAddress);
                slots[i]->end_ptr = (void *)((char *)mainMemory + slots[i]->endAddress);
            }
            auto prev_itr = itr;
            --prev_itr;
            container.erase(itr);			//Erasing the previous block before giving slot
            for(var i = 0; i < slots.size(); ++i)
            {
                prev_itr = container.insert(++prev_itr, slots[i]);	// Inserting the new slot to the vector
            }
            slots.clear();
            return true;
        }
    }
    return false;		//if allocation is not success
}

//To check wheather two slots  are buddies(same) or not

bool Binary::buddies(BinaryNode *a, BinaryNode *b)
{
   /* var add = MEMORY*2;
    if(floor( (add + a->startAddress)/(2*a->space) ) == floor( (add + b->startAddress)/(2*b->space) ))
    {
        return true;
    }
    return false; */

    if(a->endAddress == b->startAddress && !a->allocated && !b->allocated && a->space == b->space){
   	
	    return true;
    }

    return false;
    
}


/************************************************************************************
**
**
**               FUNCTION NAME 		:	check_merge
**				 DESCRIPTION		:	After deallocation merging the buddies
**				 CREATED BY			:	Team
**
**
*************************************************************************************
*/

void Binary::check_merge()
{
    auto itr = container.begin(), prev_itr = itr;
    ++itr;
    while(itr != container.end())
    {
        auto prevNode = *prev_itr, currNode = *itr;
        
        //Conditon where merging is not possible
        
        if(prevNode->allocated || currNode->allocated || (prevNode->space != currNode->space) || !buddies(prevNode, currNode))
        {
            prev_itr = itr;							
            ++itr;
            continue;
        }
        prevNode->space *= 2;			//calculate new block size
        
        prevNode->endAddress = prevNode->startAddress + prevNode->space;
        container.erase(itr);
        prev_itr = container.begin();
        itr = prev_itr;
        ++itr;
    }
}

/************************************************************************************
**
**
**               FUNCTION NAME 		:	deallocate
**				 DESCRIPTION		:	Deallocating the memory and merge them if they are buddies
**				 RETURNS			:	Returns a boolean value
**				 CREATED BY			:	Team
**
**
*************************************************************************************
*/

bool Binary::deallocate(var address)			//passing the start address of the block
{
    if(address >= MEMORY)
    {
        return false;
    }
    string request_type = "De-Allocation";
    for(auto i: container)
    {
        if(address == i->startAddress && !i->allocated)
        {
            return false;							//If the block is already free
        }
        if(address == i->startAddress)
        {
            logger.write_log(print_node(i),request_type);		//logging the request into the file
            i->allocated = false;								//set allocated to false as we deallocate the block
            i->value = 0;
            i->start_ptr = NULL;
            i->end_ptr = NULL;
            this->check_merge();						//Merging buddies
            return true;
        }
    }
    return false;
}


//To display all from vector

void Binary::display()
{
    for(auto node: container)
    {
        cout << print_node(node) << endl;
    }
}


/************************************************************************************
**
**
**               FUNCTION NAME 		:	print_node
**				 DESCRIPTION		:	Allign the message into a prpoer fromat
**				 RETURN				: 	Returns a string 
**				 CREATED BY			:	Team
**
**
*************************************************************************************
*/


string Binary::print_node(const BinaryNode *node){

    stringstream message;
    var if_ = 0;

    if(node->allocated)
    {
        if_ = node->space - node->value;			//calculating the remaining meomory
    }


    message << "> Start: "<<node->startAddress<<" | START_PTR: "<<uintptr_t(node->start_ptr)<<" | SIZE: "<<node->space;
    message<<" | Value: "<<node->value<<" | DIFF: " << if_ << " | END: "<<node->endAddress<< " | END_PTR: "<<uintptr_t(node->end_ptr);

    return message.str();
}

