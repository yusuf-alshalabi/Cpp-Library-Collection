cmake_minimum_required(VERSION 3.16)
project(Cpp-Library-Collection VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/MyLib.cpp
)

# Header files
set(HEADERS
    include/MyLib/MyString.h
    include/MyLib/MyDate.h
    include/MyLib/MyPeriod.h
    include/MyLib/MyUtil.h
)

# Create library
add_library(MyLib ${SOURCES})
target_include_directories(MyLib PUBLIC include)

# Windows specific settings
if(WIN32)
    target_compile_definitions(MyLib PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Examples
add_executable(basic_demo examples/basic_demo.cpp)
target_link_libraries(basic_demo PRIVATE MyLib)
target_include_directories(basic_demo PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(WIN32)
    target_compile_definitions(basic_demo PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Tests
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/test_main.cpp")
    enable_testing()
    add_executable(tests tests/test_main.cpp)
    target_link_libraries(tests PRIVATE MyLib)
    target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
    
    if(WIN32)
        target_compile_definitions(tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif()
    
    add_test(NAME BasicTests COMMAND tests)
endif()
