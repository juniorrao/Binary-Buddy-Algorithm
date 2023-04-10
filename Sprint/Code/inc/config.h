#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <iostream>

#include <map>

#include <string>

using namespace std;

namespace config {

  class Config { //Class to read configuration from info.txt file

    map < string, string > config; // all configuration related settings are save in key value pair in a map.

    public:
      Config(); // constructor 
    int get_Pool_Size(); // return memory pool size
    string get_Log_Path(); // return log file path

  };

}

#endif // CONFIG_H_INCLUDED
