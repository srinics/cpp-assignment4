# cpp-assignment4
HEADER:
======

Author		: Srinivasan Rajendran (M1043833)
Assignment No	: L3_04
Revision	: v1


PROBLEM STATEMENT:
=================
CPP program for reading the configuration file in Windows/Linux/MAC.
Program used to read the configuration file (config.ini) and based on the configuration 
value ( version information ) program will look for another section of configuration 
file and it will load features dll/so specified and invoke function specified in the 
configuration file


CODE:
====
	Main.cpp  		-> Invocation/Entry point
	configfile		-> Contains library/class for reading .ini file. 
				   ConfigFile.h (class ConfigFile declartion) and ConfigFile.cpp( contains class functions)
	features/feature1	-> Contains feature1 api code (Feature1.cpp) and header file (Feature1.h)
	features/feature2	-> Contains feature2 api code (Feature2.cpp) and header file (Feature2.h)
	loadlib			-> Contains api for loading dll/shared obj for both windows and linux enviroment


Build Tool:
==========
	I used CMAKE for building the source code ( because qmake not installed in my enviroment).
	CMAKE version used <3.0


Limitation:
==========
	Not tested in Mac enviroment.

Testing:
=======
	Testing completed in Window 10 - QT Creator 5.6.1
	Testing completed in Linux ( Ubuntu 18.04)

Note:
====
	Testing completed in Linux for Ubuntu enviroment in Linux enviroment just run ./CompileLinux.sh.
	It will complile and execute the binary.



