add_library(configfile STATIC ConfigFile.cpp)
if (UNIX)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_definitions(${GLIB_CFLAGS_OTHER})
target_link_libraries(configfile ${GLIB_LIBRARIES})
endif (UNIX)
