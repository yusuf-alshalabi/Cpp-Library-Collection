cmake_minimum_required(VERSION 3.16)
project(Cpp-Library-Collection VERSION 1.0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Header files
set(HEADERS
    include/MyLib/MyString.h
    include/MyLib/MyDate.h
    include/MyLib/MyPeriod.h
)

# Create header-only library
add_library(MyLib INTERFACE)
target_include_directories(MyLib INTERFACE include)

# Installation
install(FILES ${HEADERS}
    DESTINATION include/MyLib
)

# Enable testing (only if tests directory exists)
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
    enable_testing()
    add_subdirectory(tests)
endif()

# Examples (only if examples directory exists)
if(EXISTS "${CMAKE_SOURCE_DIR}/examples/CMakeLists.txt")
    add_subdirectory(examples)
endif()
