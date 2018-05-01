cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(ohf_tests)

# Catch2
set(CATCH_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../Catch2/include")
if(NOT EXISTS ${CATCH_INCLUDE_DIR})
	message(FATAL_ERROR "Catch2 submodule not found")
endif()

include_directories(${CATCH_INCLUDE_DIR})
file(GLOB_RECURSE CATCH ${PROJECT_SOURCE_DIR} "${CATCH_INCLUDE_DIR}/*")

# Tests
include_directories("../include")
include_directories(".")
file(GLOB_RECURSE TESTS_FILES ${PROJECT_SOURCE_DIR} "*.hpp" "*.cpp")

# Target
add_executable(${PROJECT_NAME} ${TESTS_FILES} ${CATCH})
target_link_libraries(${PROJECT_NAME} ohf)
add_test(NAME ${PROJECT_NAME}
		 COMMAND ${PROJECT_NAME})

# Threads
find_package(Threads REQUIRED)
if(CMAKE_THREAD_LIBS_INIT)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()

# Reporter
add_custom_target(coverage
		COMMAND lcov -d . -z
		COMMAND lcov -d . -i -c -o coverage.info
		COMMAND gdb -ex 'set confirm off' -ex run -ex quit ${PROJECT_NAME}
		COMMAND lcov -d . -c -o coverage.info
		COMMAND lcov --list coverage.info
		COMMAND curl -s https://codecov.io/bash | bash -s
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		DEPENDS ohf ${PROJECT_NAME}
		COMMENT "Make Codecov report"
)