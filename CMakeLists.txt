cmake_minimum_required(VERSION 3.5)

project(Clay_Assignment LANGUAGES CXX)
include(GNUInstallDirs)
# Enable Testing
ENABLE_TESTING()
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(test_repo)

add_executable(Clay_Assignment src/main.cpp src/repository.cpp inc/repository.h)
target_link_libraries(Clay_Assignment libal.a)
