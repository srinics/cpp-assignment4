/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (LoadLib.cpp) contains simple functions to load library for Windows/Linux/Mac
*
* */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <stdexcept>



#define LIBRARY_EXPORTS
#include "LoadLib.h"
using namespace std;
typedef void(*LibraryFunc)();


#ifdef _WIN32
#include <windows.h>
#include <atlbase.h>
#include <atlconv.h>
/*
Author: M1043833
Function Name: LoadDLL(const char*, const char *)
Description:
function to load the library and read the exported symbols of the library and invoke the func.
It will take two arguments (const char*) 1st argument contains libpath and second argument is function name.
This function will use in Windows enviroment.
*/
void LoadDLL(const char *libPath, const char *fName){
        LibraryFunc LibFunc;
        try {
                //std::cout << "Library path in LoadDLL: " << libPath << std::endl;

                /*size_t size = strlen(libPath) + 1;
                wchar_t* libPathWchar = new wchar_t[size];

                size_t outSize;
                mbstowcs_s(&outSize, libPathWchar, size, libPath, size - 1);
                HINSTANCE hInstLibrary = LoadLibrary(lpath);*/

                HINSTANCE hInstLibrary = LoadLibrary(TEXT(libPath));



                if (hInstLibrary)
                {
                        LibFunc = (LibraryFunc)GetProcAddress(hInstLibrary, fName);

                        if (LibFunc)
                        {
                                std::cout << "Calling Library Function: " << std::endl;
                                LibFunc();
                        }
                        else{
                                std::cout << "In DLL "<< libPath << " funciton "<< fName << " not available" << std::endl;
                                throw std::runtime_error("DLL funciton is not available");
                        }
                        FreeLibrary(hInstLibrary);
                        //free(libPathWchar);
                }
                else
                {
                        std::cout << "DLL Failed To Load!" << std::endl;
                        //free(libPathWchar);
                        throw std::runtime_error("DLL Failed To Load");
                }
        }
        catch (std::runtime_error){
                throw;
        }
}
#else
#include <dlfcn.h>
/*
Author: M1043833
Function Name: LoadSharedObject(const char*, const char *)
Description:
function to load the library and read the exported symbols of the library and invoke the func.
It will take two arguments (const char*) 1st argument contains libpath and second argument is function name.
This function will use in Linux enviroment.
*/
void LoadSharedObject(const char* libPath, const char *funcName){
        try{

                void* handle = dlopen(libPath, RTLD_LAZY);

                if (!handle) {
                        std::cout  << "Cannot open library: " << dlerror() << std::endl;
                        throw std::runtime_error("Shared object open error");
                }

                // reset errors
                dlerror();
                std::cout  << "Function in symbol:" << funcName << std::endl;
                LibraryFunc LibFunc = (LibraryFunc) dlsym(handle, funcName);
                const char *dlsym_error = dlerror();
                if (dlsym_error) {
                        std::cout << "Cannot load symbol 'hello': " << dlsym_error <<
            '\n';
                        dlclose(handle);
                        throw std::runtime_error("Shared object open error");
                }

                LibFunc();
                dlclose(handle);
        }
        catch ( std::exception ){
                throw;
        }
}
#endif


/*
Author: M1043833
Function Name: LoadLibraryFunc(const char *, const char *)
Description:
Simple function to load the library and read the exported symbols of the library and invoke the func.
It will take two arguments (const char*) 1st argument contains libpath and second argument is function name.
It is wrapper function based on the enviroment it will invoke LoadDLL or LoadSharedObject.
*/
bool LoadLibraryFunc(const char *libPath, const char *funcName){

        try{

                if (!libPath || !funcName || (strlen(libPath) == 0) || (strlen(funcName) == 0)){
                        throw std::runtime_error("Invalid library name and/or funciton name");
                        return false;
                }

#ifdef _WIN32
                LoadDLL(libPath, funcName);
#else
                LoadSharedObject(libPath, funcName);
#endif

        }
        catch (std::runtime_error &ex){
                std::cout << "Error in Library load: " << ex.what() << std::endl;
                return false;
        }
        return true;
}
