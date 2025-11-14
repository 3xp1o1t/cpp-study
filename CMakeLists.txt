cmake_minimum_required(VERSION 3.15)
project(cpp_study LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include headers from include/
include_directories(${CMAKE_SOURCE_DIR}/include)

option(BUILD_EXAMPLES "Build platform example executables" ON)
if(BUILD_EXAMPLES)
	# LeetCode problems
	add_executable(leetcode_0001 src/platforms/leetcode/easy/0001_two_sum.cpp)
	target_include_directories(leetcode_0001 PRIVATE ${CMAKE_SOURCE_DIR}/include)
endif()

# Playgrounds (debugging & experimentation)
option(BUILD_PLAYGROUNDS "Build playground executables" ON)
if(BUILD_PLAYGROUNDS)
	add_executable(debug_arrays src/playground/debug_arrays.cpp)
	target_include_directories(debug_arrays PRIVATE ${CMAKE_SOURCE_DIR}/include)
	
	add_executable(debug_array_algorithms src/playground/debug_array_algorithms.cpp)
	target_include_directories(debug_array_algorithms PRIVATE ${CMAKE_SOURCE_DIR}/include)

  add_executable(debug_linked_list src/playground/debug_linked_list.cpp)
  target_include_directories(debug_linked_list PRIVATE ${CMAKE_SOURCE_DIR}/include)
endif()

# Tests
add_subdirectory(tests)

