cmake_minimum_required(VERSION 3.16)
project(Cpp-Library-Collection VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/MyString.cpp
    src/MyDate.cpp
    src/MyPeriod.cpp
)

# Header files
set(HEADERS
    include/MyLib/MyString.h
    include/MyLib/MyDate.h
    include/MyLib/MyPeriod.h
)

# Create library
add_library(MyLib ${SOURCES} ${HEADERS})

# Set include directories for the library
target_include_directories(MyLib PUBLIC include)

# Installation
install(TARGETS MyLib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${HEADERS}
    DESTINATION include/MyLib
)

# Enable testing
enable_testing()

# Add tests
add_subdirectory(tests)

# Examples
add_subdirectory(examples)
