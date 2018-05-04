cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(ohf)

# Set standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Compiler options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/W4")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
    endif()
endif()

# Options
## DTLS
option(ENABLE_DTLS "Would enable DTLS" OFF)
if(ENABLE_DTLS)
    add_definitions(-DOKHTTPFORK_DTLS)
endif()

## Tests
enable_testing()
if(BUILD_TESTING)
    # Coverage
    if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
        if(NOT CMAKE_COMPILER_IS_GNUCXX)
            message(FATAL_ERROR "Sorry, your compiler does not supported yet")
        endif()

        set(CMAKE_BUILD_TYPE "Debug")

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()

    add_subdirectory(tests)
endif()

## Examples
option(BUILD_EXAMPLES "Would compile examples" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Files
## Common
file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${PROJECT_SOURCE_DIR} "include/*.hpp")
file(GLOB_RECURSE LIB_FILES     RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp" "src/*.hpp")

## For different systems
if(WIN32)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/unix/*")
elseif(UNIX)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/win32/*")
endif()
list(REMOVE_ITEM LIB_FILES ${FILES})

add_library(ohf ${INCLUDE_FILES} ${LIB_FILES})

# Libraries
## Find
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

## Include
include_directories(include)
include_directories(${OPENSSL_INCLUDE_DIR})

## Link
target_link_libraries(ohf ${OPENSSL_LIBRARIES})
target_link_libraries(ohf ${CMAKE_THREAD_LIBS_INIT})
if(WIN32)
    target_link_libraries(ohf ws2_32)
    target_link_libraries(ohf crypt32)
endif()

# Install
install(FILES cmake/FindOHF.cmake DESTINATION cmake)
install(DIRECTORY include/ohf DESTINATION include)
install(TARGETS ohf
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)