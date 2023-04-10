/************************************************************************************
**
**        DESCRIPTION    :    Group-6(Binary Buddy Algorithm )
**
**       last updated    :    09-04-2023
**
**
************************************************************************************/
#include "../inc/config.h"

#include <iostream>

#include <fstream>

#include <sstream>

#include <map>

#include <string>
/************************************************************************************
**     FUNCTION NAME     :     Config
**
**    DESCRIPTION        :     setting of pool_size and log_path by reading from file.
**
**     RETURNS           :    no return type for constructor
**
**
**     Created by        :     Team
************************************************************************************/
using namespace std;
namespace config {

  Config::Config() {

    config["pool_Size"] = "1024";
    config["log_Path"] = "log.txt";

    string default_Data = "pool_Size=" + config["pool_Size"] +", "+"log_Path=" + config["log_Path"];
    ifstream config_file;//for reading the file we use ifstream

    config_file.open("info.txt");//opening of info.txt

    if (!config_file.is_open()) {

      fstream new_file;
      new_file.open("info.txt", ios::out);

      new_file << default_Data;

      new_file.close();//closing of file

    }

    config_file.close();

    ifstream input_file("info.txt");
    string line;

    if (input_file.is_open()) {//checking whether the input file is open or not
      while (getline(input_file, line)) { //getline is used to read file line by line
        stringstream line_stream(line);
        string key, value; 

        while (getline(line_stream, key, '=') && getline(line_stream, value, ',')) {//'=' and ',' are delimiters to separate the text
          if (key == "pool_Size" || key == "log_Path") {
            config[key] = value;
          }

        }
      }

      input_file.close();//closing the input file

    }

  }
/************************************************************************************
**     FUNCTION NAME     :     get_Pool_Size
**
**    DESCRIPTION        :     return the pool size of memory to test.
**
**     RETURNS           :    Integer
**
**
**     Created by        :     Team
************************************************************************************/

  int Config::get_Pool_Size() {
    return (stoi(config["pool_Size"]));//returns a string then converting the string to integer and returns
  }
/************************************************************************************
**     FUNCTION NAME     :     get_Log_Path
**
**    DESCRIPTION        :     return the file name of log file  by reading from config file.
**
**     RETURNS           :    string
**
**
**     Created by        :     Team
************************************************************************************/

  string Config::get_Log_Path() {
    return config["log_Path"];//returns a string
  }

};




