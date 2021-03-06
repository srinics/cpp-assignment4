/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (Main.cpp) contains main function*
* */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <algorithm>


#include "ConfigFile.h"
#include "LoadLib.h"
using namespace std;

int main(int argv, char **argc){

    try{
        char vSection[8];
        std::string libName;
        std::string apiName;

        std::unique_ptr<ConfigFile> c(new ConfigFile(CONFIG_FILE));
#ifdef _WIN32
        sprintf_s (vSection, "%d.%d", c->GetInteger("Version", "majorNumber", -1), c->GetInteger("Version", "minorNumber", -1) );
        libName = c->GetString(vSection, "libWindows", "");
#else
        libName.append(FEATURE_LIBS);
        sprintf (vSection, "%d.%d", c->GetInteger("Version", "majorNumber", -1), c->GetInteger("Version", "minorNumber", -1) );
        libName.append(c->GetString(vSection, "libLinux", ""));
#endif

        apiName = c->GetString(vSection, "api", "");

        if(strstr(vSection, "-1") != NULL || libName.length() == strlen(FEATURE_LIBS) || apiName.length() == strlen(FEATURE_LIBS)){
            throw std::runtime_error("Invalid Configuration data....");
        }
        std::cout << "Version " << vSection << std::endl;
        std::cout << "Library:" << libName << std::endl;
        std::cout << "API: " << apiName << std::endl;


        LoadLibraryFunc(libName.c_str(), apiName.c_str());

     }catch(std::runtime_error & ex){
        std::cout << "Exception occured: "<< ex.what() <<std::endl;
     }
     return 0;
}
