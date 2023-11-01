cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ricci LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(brokkr REQUIRED)
brokkr_deduce_project_version()
include(CTest)

brokkr_library(${PROJECT_NAME})

brokkr_package()
