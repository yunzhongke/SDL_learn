cmake_minimum_required(VERSION 3.0)
project(SDL_test)

find_package(SDL REQUIRED)
if(SDL_FOUND)
    message(STATUS ${SDL_VERSION_STRING})
    include_directories(${SDL_INCLUDE_DIR})
    #add_executable(${PROJECT_NAME} test.c)
    #target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARY})
endif()

find_package(SDL_image REQUIRED)
if(SDL_IMAGE_FOUND)
    message(STATUS ${SDL_IMAGE_VERSION_STRING})
    include_directories(${SDL_IMAGE_INCLUDE_DIRS})
endif()

aux_source_directory(./test SRC_LIST)

foreach(sourcefile ${SRC_LIST})
    string(REPLACE ".c" "" sourcename ${sourcefile})
    string(REPLACE "./test/" "" sourcename ${sourcename})
    #message("=== " ${sourcename})
    add_executable(${sourcename} ${sourcefile})
    target_link_libraries(${sourcename} ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES})
endforeach(sourcefile ${SRC_LIST})
