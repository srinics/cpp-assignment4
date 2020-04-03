#include "ConfigFile.h"


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
    //std::cout << "File path: " << path << std::endl;
    SetConfigFileStr(path);

}

std::string ConfigFile::GetConfigFileStr() const{
    return configFileStr;
}
void ConfigFile::SetConfigFileStr(const std::string & p){
    configFileStr = p;
}


ConfigFile::~ConfigFile(){
    std::cout << "ConfigFile destructor....." << std::endl;
}


std::string ConfigFile::GetString(const std::string & section, const std::string  & attr, std::string default_value="none"){

    char iniValue[256];
#ifdef _WIN32
    GetPrivateProfileString(section.c_str(), attr.c_str(), default_value.c_str(), iniValue, 256, GetConfigFileStr().c_str());
#else
    std::cout << "GetString in Linux Env......" << std::endl;
#endif
    std::cout << "StringValue: in ["<< section <<"][" << attr << "]:" << iniValue << std::endl;
    //std::cout << "File: "<< GetConfigFileStr().c_str() << std::endl;
    return std::string(iniValue);
}



int ConfigFile::GetInteger(const std::string & section, const std::string  & attr, int default_value=0){
    int iniValue=0;
#ifdef _WIN32
    iniValue = GetPrivateProfileInt(section.c_str(), attr.c_str(), default_value, GetConfigFileStr().c_str());
#else
    std::cout << "GetInteger in Linux Env......" << std::endl;
#endif
    std::cout << "IntegerValue: in ["<< section <<"][" << attr << "]:" << iniValue << std::endl;
    //std::cout << "File: "<< GetConfigFileStr().c_str() << std::endl;
    return iniValue;
}
