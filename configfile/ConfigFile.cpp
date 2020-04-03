#include "ConfigFile.h"

#ifndef _WIN32

bool ConfigFile::InitConfigLinux(const char *path){
	g_autoptr(GError) error = NULL;
	keyFile = g_key_file_new ();

	if (!g_key_file_load_from_file (keyFile, path, G_KEY_FILE_NONE,  &error))
	{
	    throw std::runtime_error("Error in config file load linux");
	}
	return true;

}
#endif

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


ConfigFile::~ConfigFile(){
    std::cout << "ConfigFile destructor....." << std::endl;
}


std::string ConfigFile::GetString(const std::string & section, const std::string  & attr, std::string default_value="none"){

    char iniValue[256];
#ifdef _WIN32
    GetPrivateProfileString(section.c_str(), attr.c_str(), default_value.c_str(), iniValue, 256, GetConfigFileStr().c_str());
#else
    std::cout << "GetString in Linux Env......" << std::endl;
    g_autoptr(GError) error = NULL;
   
    gchar *value = g_key_file_get_string (keyFile,
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



int ConfigFile::GetInteger(const std::string & section, const std::string  & attr, int default_value=0){
    int iniValue=0;
#ifdef _WIN32
    iniValue = GetPrivateProfileInt(section.c_str(), attr.c_str(), default_value, GetConfigFileStr().c_str());
#else
    std::cout << "GetInteger in Linux Env......" << std::endl;

    g_autoptr(GError) error = NULL;
    iniValue = g_key_file_get_integer (keyFile,
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
