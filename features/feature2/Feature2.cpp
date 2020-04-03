#define LIBRARY2_EXPORTS

#include <iostream>
#include "Feature2.h"
extern "C" void LIBRARY_API Feature2(){
    std::cout << "Feature2 library loaded and Feature2 api exectuting........" << std::endl;
}
