cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(okhttp-fork)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Compiler options
if(MSVC)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/W4")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
endif()

# Options
option(ENABLE_DTLS "Would enable DTLS" OFF)
if(ENABLE_DTLS)
    add_definitions(-DOKHTTPFORK_DTLS)
endif()

# Tests
enable_testing()
if(BUILD_TESTING)
    # Coverage
    if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
        set(CMAKE_BUILD_TYPE "Debug")

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()

    add_subdirectory(tests)
endif()

# Examples
option(BUILD_EXAMPLES "Would compile examples" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Common files
include_directories(include)
file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${PROJECT_SOURCE_DIR} "include/*.hpp")
file(GLOB_RECURSE LIB_FILES     RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp" "src/*.hpp")

# Files for different systems
if(WIN32)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/unix/*")
elseif(UNIX)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/win32/*")
endif()
list(REMOVE_ITEM LIB_FILES ${FILES})

add_library(ohf ${INCLUDE_FILES} ${LIB_FILES})

# Libraries
# OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ohf ${OPENSSL_LIBRARIES})

    if(WIN32)
        target_link_libraries(ohf crypt32)
    endif()
endif()

# Threads
find_package(Threads REQUIRED)
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(ohf ${CMAKE_THREAD_LIBS_INIT})
endif()

# Socket
if (WIN32)
    target_link_libraries(ohf ws2_32)
endif()

# Install
install(DIRECTORY include/ohf DESTINATION include)
install(TARGETS ohf
        RUNTIME       DESTINATION bin
        LIBRARY       DESTINATION lib
        ARCHIVE       DESTINATION lib)