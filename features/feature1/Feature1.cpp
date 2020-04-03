/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (Feature1.cpp) contains simple functions to test dll/so
*
* */
#define LIBRARY1_EXPORTS
#include <iostream>
#include "Feature1.h"


/*
Author: M1043833
Function Name: Feature1
Description:
Simple function just print the function function and it has no arguments and no return type
*/
extern "C" void LIBRARY_API Feature1(){
    std::cout << "Feature1 library loaded and Feature1 api exectuting........" << std::endl;
}
