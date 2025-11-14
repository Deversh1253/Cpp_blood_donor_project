cmake_minimum_required(VERSION 3.16)
project(BloodLifeApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Widgets Sql REQUIRED)

add_subdirectory(include)
add_subdirectory(src)

