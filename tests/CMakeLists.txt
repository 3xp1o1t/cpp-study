cmake_minimum_required(VERSION 3.15)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.15.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Recoger todos los tests .cpp dentro de tests/
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/tests/*.cpp)

if(TEST_SOURCES)
	add_executable(unit_tests ${TEST_SOURCES})
	target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
	target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

	include(GoogleTest)
	gtest_discover_tests(unit_tests)
else()
	message(STATUS "No test sources found in tests/ folder.")
endif()

