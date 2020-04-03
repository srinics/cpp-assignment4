#define LIBRARY1_EXPORTS
#include <iostream>
#include "Feature1.h"


extern "C" void LIBRARY_API Feature1(){
    std::cout << "Feature1 library loaded and Feature1 api exectuting........" << std::endl;
}
