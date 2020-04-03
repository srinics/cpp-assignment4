#ifndef __CONFIGFILE__
#define __CONFIGFILE__

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <stdexcept>

#ifdef _WIN32
#define F_OK    0
#include "io.h"
#include <Windows.h>
#include <WinBase.h>
#else
#include <unistd.h>
#include <glib.h>
#endif
using namespace std;


class ConfigFile{

private:
    std::string configFileStr;
#ifndef _WIN32	
    GKeyFile *keyFile;
#endif


public:
    ConfigFile(){}
    ConfigFile(const std::string & file);
    std::string GetConfigFileStr() const;
    void SetConfigFileStr(const std::string &p);
#ifndef _WIN32
    bool InitConfigLinux(const char *p);
    void SetKeyFilePtr(GKeyFile *p);
    GKeyFile* GetKeyFilePtr();
#endif
    std::string GetString(const std::string & section, const std::string & attr, std::string defaultValue);
    int GetInteger(const std::string & section, const std::string & attr, int defaultValue);
    ~ConfigFile();
};


#endif


