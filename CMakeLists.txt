cmake_minimum_required(VERSION 3.16)

project(nanotekspice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(COVERAGE "Build with gcov/llvm-cov instrumentation" OFF)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
    include
    include/Components
    include/Components/Chipset
    include/Components/Core
    include/Components/Exception
    include/Components/IO
    include/Components/Factory
    include/Components/Operators
    include/Parser
    include/Circuit
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

if(COVERAGE)
  target_compile_options(${PROJECT_NAME} PRIVATE --coverage -O0 -g)
  target_link_options(${PROJECT_NAME} PRIVATE --coverage)
endif()
