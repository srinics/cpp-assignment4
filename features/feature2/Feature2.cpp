/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (Feature2.cpp) contains simple functions to test dll/so
*
* */

#define LIBRARY2_EXPORTS

/*
Author: M1043833
Function Name: Feature2
Description:
Simple function just print the function function and it has no arguments and no return type
*/
#include <iostream>
#include "Feature2.h"
extern "C" void LIBRARY_API Feature2(){
    std::cout << "Feature2 library loaded and Feature2 api exectuting........" << std::endl;
}
