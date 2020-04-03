/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (LoadLib.h) contains contains prototype for LoadLib.cpp
*
* */

#ifndef LOADLIB_H
#define LOADLIB_H

#ifdef _WIN32

#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

#else
#define LIBRARY_API

#endif



LIBRARY_API bool LoadLibraryFunc(const char *libPath, const char *funcName);
#ifdef _WIN32
LIBRARY_API void LoadDLL(const char*, const char*);
#else
LIBRARY_API void LoadSharedObject(const char*, const char*);
#endif


#endif // LOADLIB_H
