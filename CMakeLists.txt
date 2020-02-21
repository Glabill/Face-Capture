cmake_minimum_required(VERSION 3.0.0)
project(F4C3 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(F4C3 
F4C3/sources/main.cpp
F4C3/sources/Core.cpp
F4C3/sources/StreamManager.cpp
F4C3/sources/ImageProcessor.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
