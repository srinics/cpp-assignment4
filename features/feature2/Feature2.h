/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (Feature2.h) contains contains prototype for Feature2.cpp
*
* */
#ifndef FEATURE2_H
#define FEATURE2_H

#ifdef _WIN32
#ifdef LIBRARY2_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport) __stdcall
#endif
#else
#define LIBRARY_API
#endif

extern "C" void LIBRARY_API Feature2();

#endif // FEATURE2_H

