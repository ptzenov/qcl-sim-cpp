cmake_minimum_required(VERSION 3.0) 
project(QCLSIM)
 
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
set(CMAKE_CXX "g++")


find_package(Matlab REQUIRED)



#Bring the headers, such as Student.h into the project
include_directories(
	include
	${Matlab_INCLUDE_DIRS}
	)


link_directories(
	"../lib"
	${Matlab_LIBRARY_DIRS}
	)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(QCLSIM ${SOURCES})
target_link_libraries(QCLSIM gsl gslcblas mx mat)



