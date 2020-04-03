/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (ConfigFile.cpp) contains api of the class ConfigFile*
* */


#include "ConfigFile.h"

#ifndef _WIN32
/*
Author: M1043833
Function Name: InitConfigLinux(const char *path))
Description:
This used to initiate key configuration ptr.
This function will use in Linux enviroment.
*/
bool ConfigFile::InitConfigLinux(const char *path){
    g_autoptr(GError) error = NULL;
    SetKeyFilePtr(g_key_file_new ());

    if (!g_key_file_load_from_file (GetKeyFilePtr(), path, G_KEY_FILE_NONE,  &error))
    {
        throw std::runtime_error("Error in config file load linux");
    }
    return true;

}
GKeyFile * ConfigFile::GetKeyFilePtr(){
    return keyFile;
}
void ConfigFile::SetKeyFilePtr(GKeyFile *p){
    keyFile = p;
}
#endif


/*
Author: M1043833
Description:
Parameterize constructor for ConfigFile class. Getting config file as a string argument and check the file
presence and if present and it will initiate configFileStr.
*/
ConfigFile::ConfigFile(const std::string & path){


    if(path.length() == 0 ){
        std::cout << "Invalid length in path" << std::endl;
        throw std::runtime_error("Invalid file");
    }
    if( access( path.c_str(), F_OK ) != -1 ){
        std::cout << "ConfigFile constructor....." << std::endl;
    }
    else{
        std::cout << "Error, Invalid File path: " << path.c_str() << std::endl;
        throw std::runtime_error("Invalid file");
    }

#ifndef _WIN32
    InitConfigLinux(path.c_str());
#endif

    //std::cout << "File path: " << path << std::endl;
    SetConfigFileStr(path);

}

std::string ConfigFile::GetConfigFileStr() const{
    return configFileStr;
}
void ConfigFile::SetConfigFileStr(const std::string & p){
    configFileStr = p;
}

/*
Author: M1043833
Description:
Destructor for ConfigFile class.
*/
ConfigFile::~ConfigFile(){
    std::cout << "ConfigFile destructor....." << std::endl;
#ifndef _WIN32
    if(GetKeyFilePtr()){
        g_key_file_free(GetKeyFilePtr());
    }
#endif
}

/*
Author: M1043833
Function Name: GetString(const std::string & section, const std::string  & attr, std::string default_value="none")
Description:
This used to used to get string value from the configuration file(.ini) and
it will take section name, attribute name and default value. And it will return the configuration
value else return default value in case invalid section/attr name.
*/
std::string ConfigFile::GetString(const std::string & section, const std::string  & attr, std::string default_value="none"){

    char iniValue[256];
#ifdef _WIN32
    GetPrivateProfileString(section.c_str(), attr.c_str(), default_value.c_str(), iniValue, 256, GetConfigFileStr().c_str());
#else
    std::cout << "GetString in Linux Env......" << std::endl;
    g_autoptr(GError) error = NULL;

    gchar *value = g_key_file_get_string (GetKeyFilePtr(),
                              section.c_str(),
                              attr.c_str(),
                              &error);
    if(error){
    strcpy(iniValue, default_value.c_str());
    }else{
    strcpy(iniValue, value);
    g_free(value);
    }
#endif

    std::cout << "StringValue: in ["<< section <<"][" << attr << "]:" << iniValue << std::endl;
    //std::cout << "File: "<< GetConfigFileStr().c_str() << std::endl;
    return std::string(iniValue);
}


/*
Author: M1043833
Function Name: GetInteger(const std::string & section, const std::string  & attr, std::string default_value="none")
Description:
This used to used to get integer value from the configuration file(.ini) and
it will take section name, attribute name and default value. And it will return the configuration
value else return default value in case invalid section/attr name.
*/
int ConfigFile::GetInteger(const std::string & section, const std::string  & attr, int default_value=0){
    int iniValue=0;
#ifdef _WIN32
    iniValue = GetPrivateProfileInt(section.c_str(), attr.c_str(), default_value, GetConfigFileStr().c_str());
#else
    std::cout << "GetInteger in Linux Env......" << std::endl;

    g_autoptr(GError) error = NULL;
    iniValue = g_key_file_get_integer (GetKeyFilePtr(),
                              section.c_str(),
                              attr.c_str(),
                              &error);
    if(error){
        iniValue=default_value;
    }

#endif
    std::cout << "IntegerValue: in ["<< section <<"][" << attr << "]:" << iniValue << std::endl;
    //std::cout << "File: "<< GetConfigFileStr().c_str() << std::endl;
    return iniValue;
}
