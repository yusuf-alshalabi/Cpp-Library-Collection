cmake_minimum_required(VERSION 3.16)

# Examples for C++ Library Collection

# Basic demo example
add_executable(basic_demo basic_demo.cpp)

# Link with the library
target_link_libraries(basic_demo PRIVATE MyLib)

# Set C++ standard
target_compile_features(basic_demo PRIVATE cxx_std_17)

# Add include directories
target_include_directories(basic_demo PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Windows specific settings
if(WIN32)
    target_compile_definitions(basic_demo PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
