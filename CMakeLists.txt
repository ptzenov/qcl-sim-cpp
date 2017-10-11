cmake_minimum_required(VERSION 2.8) 
project(QCLSIM)
 
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
set(CMAKE_CXX "g++")

#Bring the headers, such as Student.h into the project
include_directories(
	include
	"/mnt/SHARED/Matlab_Linux/extern/include"
	)


link_directories(
	"../lib"
	"/mnt/SHARED/Matlab_Linux/bin/glnxa64"
	)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(QCLSIM ${SOURCES})
target_link_libraries(QCLSIM gsl gslcblas mx mat)



