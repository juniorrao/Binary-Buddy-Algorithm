/************************************************************************************
**
**        DESCRIPTION    :    Group-6(binary buddy system)
**
**       last updated    :    09-04-2023
**
**
************************************************************************************/
#include "../inc/log.h"

#include <chrono>

#include <ctime>

#include <iostream>
#include <string>

#include<fstream>
/************************************************************************************
**     FUNCTION NAME     :     get time_stamp

**    DESCRIPTION        :    returns date and time 

**
**     RETURNS           :    returns data and time when allocate and free request are made
**
**
**     Created by        :     Team
************************************************************************************/

using namespace std;
namespace logger {

  string Logger::get_timestamp()//this method return timestamp
   {
    auto now = chrono::system_clock::now(); //this is a predefined library which returns present time
    time_t t = chrono::system_clock::to_time_t(now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime( & t));// this converts date and time to string
    return string(buffer);
  }
 /************************************************************************************
**     FUNCTION NAME     :    write_log

**    DESCRIPTION        :    displays all malloc and free requests

**
**     RETURNS           :    void
**
**
**     Created by        :    Team
************************************************************************************/ 
  

 void Logger::write_log(const string message, const string request_type) // this is a method which writes request into log file 
 {
    ofstream out_File;
    out_File.open(log_path, ios::app);//opens log file in append mode

    if (out_File) {
      out_File << "Request DateTime: " << get_timestamp() << " | " << request_type << " :- " << endl; //this writes timestamp and request_type in log file
      out_File << message << endl;//displays all malloc and free memory requests.
    }

    out_File.close();

  }


}
