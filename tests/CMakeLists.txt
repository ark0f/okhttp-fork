project(ohf_tests)

# Files
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Catch2/CMakeLists.txt")
	message(FATAL_ERROR "Catch2 submodule not found")
endif()

set(CATCH_INCLUDE_DIR "Catch2/include")

include_directories(${CATCH_INCLUDE_DIR})
include_directories("../include")

file(GLOB_RECURSE CATCH RELATIVE ${PROJECT_SOURCE_DIR} "${CATCH_INCLUDE_DIR}/*")
file(GLOB INCLUDE RELATIVE ${PROJECT_SOURCE_DIR} "./*.hpp")
file(GLOB LIB RELATIVE ${PROJECT_SOURCE_DIR} "./*.cpp")

# Coverage
option(COVERAGE "Enable coverage reporter" OFF)
if(COVERAGE)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/coveralls-cmake/cmake")

	include(Coveralls)

	coveralls_turn_on_coverage()
	coveralls_setup("${LIB}" OFF "${PROJECT_SOURCE_DIR}/coveralls-cmake/cmake")
endif()

# Target
add_executable(${PROJECT_NAME} ${INCLUDE} ${LIB} ${CATCH})
target_link_libraries(${PROJECT_NAME} ohf)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
