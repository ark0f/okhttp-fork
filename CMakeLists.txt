cmake_minimum_required(VERSION 3.1)
project(OkHttpFork)

set(CMAKE_CXX_STANDARD 11)

# Compiler options
if(MSVC)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/W4")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
endif()

# Options
option(DTLS "Would use DTLS" OFF)
if(DTLS)
    add_definitions(-DOKHTTPFORK_DTLS)
endif()

option(TESTS "Unit-tests for ${PROJECT_NAME} using Catch2" ON)
if(TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Common files
include_directories(include)

file(GLOB_RECURSE SOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR} "include/*.hpp" "src/*.cpp")

# Files for different systems
if(WIN32)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/unix/*")
elseif(UNIX)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/win32/*")
endif()
list(REMOVE_ITEM SOURCE_FILES ${FILES})

add_library(ohf ${SOURCE_FILES})

# Libraries
# OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ohf ${OPENSSL_LIBRARIES})
endif()

# Socket
if (WIN32)
    target_link_libraries(ohf wsock32)
endif()

# Install
install(DIRECTORY "include/ohf/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ohf")
install(TARGETS ohf
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
