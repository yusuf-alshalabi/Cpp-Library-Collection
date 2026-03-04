cmake_minimum_required(VERSION 3.16)

# Tests for C++ Library Collection

# Enable testing
enable_testing()

# Test executable
add_executable(tests test_main.cpp)

# Link with the library
target_link_libraries(tests PRIVATE MyLib)

# Set C++ standard
target_compile_features(tests PRIVATE cxx_std_17)

# Add include directories
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Windows specific settings
if(WIN32)
    target_compile_definitions(tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Register test
add_test(NAME BasicTests COMMAND tests)
