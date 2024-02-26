cmake_minimum_required(VERSION 3.26.1 FATAL_ERROR)

set(PROJECT_NAME MatrixBS2D)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include_directories(D:/SDL2/include)

link_directories(D:/SDL2/lib/x64)

add_executable(${PROJECT_NAME}
        src/main.cpp
        )
		
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2.lib SDL2main.lib SDL2test.lib)
		