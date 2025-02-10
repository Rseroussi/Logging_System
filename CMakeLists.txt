cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Logging_System)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Logging_System main.cpp)

# Include directories
include_directories(include)
include_directories(src)

# add thread library
find_package(Threads REQUIRED)
target_link_libraries(Logging_System Threads::Threads)


# Link libraries (if any)
# target_link_libraries(Logging_System <library_name>)