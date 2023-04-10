/************************************************************************************
**
**        DESCRIPTION    :    Group-6(binary buddy system)
**
**       last updated    :    09-04-2023
**
**
************************************************************************************/
#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include <iostream>
#include <string>
/************************************************************************************
**     FUNCTION NAME     :    logger class

**    DESCRIPTION        :    constructors and methods in the logger class

**
**     RETURNS           :    logs all malloc and free requests made by the user
**
**
**     Created by        :     Team
************************************************************************************/

using namespace std;
namespace logger{


    class Logger  //base class named as logger 
	 {

   
    private:
	   string log_path;


    public:

        Logger(string log_path): log_path(log_path){}      //this is a constructor of logger class
        string get_timestamp();                       //this is a method of logger class
        void write_log(const string,const string);
	


    };


}


#endif // LOG_H_INCLUDED
