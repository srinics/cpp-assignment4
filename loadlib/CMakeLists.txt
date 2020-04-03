add_library(loadlib SHARED LoadLib.cpp)
if (UNIX)
target_link_libraries(loadlib -ldl)
endif (UNIX)
