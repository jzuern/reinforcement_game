cmake_minimum_required(VERSION 2.6)
project(project_0)


add_definitions(-std=c++11 -Wall -Werror)

set( project_sources
   src/main.cpp
   src/SimulatedDisk.cpp
)

include_directories(include)



add_executable(project0
	${project_sources})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(project0 ${SFML_LIBRARIES})
endif()

