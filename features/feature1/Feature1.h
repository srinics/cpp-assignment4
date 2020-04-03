#ifndef FEATURE1_H
#define FEATURE1_H

#ifdef _WIN32
#ifdef LIBRARY1_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport) __stdcall
#endif
#else
#define LIBRARY_API
#endif

extern "C" void LIBRARY_API Feature1();

#endif // FEATURE1_H
