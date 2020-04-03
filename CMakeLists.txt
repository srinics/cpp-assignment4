project(assignment4)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/loadlib/ ${PROJECT_SOURCE_DIR}/configfile)
SET(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)
SET(CFG_FILE_PATH ${OUTPUT_DIR}/configs)
SET(CFG_FILE_NAME config.ini)

file(MAKE_DIRECTORY ${CFG_FILE_PATH})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)

add_compile_definitions(CONFIG_FILE="${CFG_FILE_PATH}/${CFG_FILE_NAME}")

add_subdirectory (features)
add_subdirectory (loadlib)
add_subdirectory (configfile)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${CFG_FILE_NAME} ${CFG_FILE_PATH}/ COPYONLY)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries( ${PROJECT_NAME} loadlib configfile)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/${CFG_FILE_NAME} ${CFG_FILE_PATH}/  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${CFG_FILE_NAME}"
)






