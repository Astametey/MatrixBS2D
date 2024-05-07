cmake_minimum_required(VERSION 3.26.1 FATAL_ERROR)

set(PROJECT_NAME MatrixBS2D)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include_directories(D:/SDL2/include)
include_directories(D:/SDL2_image/include)
include_directories(D:/SDL2_ttf/include)

link_directories(D:/SDL2/lib/x64)
link_directories(D:/SDL2_image/lib/x64)
link_directories(D:/SDL2_ttf/lib/x64)

add_executable(${PROJECT_NAME}
        src/main.cpp
		
		src/game.h
		
		src/level.h
		src/pngLoader_SDL2.h
		src/camera.h
		src/Entity.h
		src/events.h
		
		src/tinyxml/tinystr.cpp
		src/tinyxml/tinyxml.cpp
		src/tinyxml/tinyxml2.cpp
		src/tinyxml/tinyxmlerror.cpp
		src/tinyxml/tinyxmlparser.cpp
		
		src/tinyxml/tinyxml.h
		src/tinyxml/tinyxml2.h
		src/tinyxml/tinystr.h
        )
		
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources 
	$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources ../build/resources)
		
target_link_libraries(${PROJECT_NAME} PRIVATE 
	SDL2.lib 
	SDL2main.lib 
	SDL2test.lib 
	SDL2_image.lib
	SDL2_ttf.lib)
		