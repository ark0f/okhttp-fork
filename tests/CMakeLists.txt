cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(ohf_tests)

# Catch2
set(CATCH_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../Catch2/include")
if(NOT EXISTS ${CATCH_INCLUDE_DIR})
	message(FATAL_ERROR "Catch2 submodule not found")
endif()

file(GLOB_RECURSE CATCH_FILES ${PROJECT_SOURCE_DIR} "${CATCH_INCLUDE_DIR}/*")

# Tests
file(GLOB_RECURSE TESTS_FILES ${PROJECT_SOURCE_DIR} "*.hpp" "*.cpp")
add_executable(ohf_tests ${TESTS_FILES} ${CATCH_FILES})
add_test(NAME ohf_tests COMMAND ohf_tests)

# Libraries
## Find
find_package(Threads REQUIRED)

## Include
include_directories(${CATCH_INCLUDE_DIR})
include_directories(.)
include_directories(../include)

## Link
target_link_libraries(ohf_tests ohf)
target_link_libraries(ohf_tests ${CMAKE_THREAD_LIBS_INIT})

# Reporter
add_custom_target(coverage
		COMMAND lcov -d . -z
		COMMAND lcov -d . -i -c -o coverage.info
		COMMAND gdb -ex 'set confirm off' -ex run -ex quit ohf_tests
		COMMAND lcov -d . -c -o coverage.info
		COMMAND lcov --list coverage.info
		COMMAND curl -s https://codecov.io/bash | bash -s
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		DEPENDS ohf ohf_tests
		COMMENT "Make Codecov report"
)