cmake_minimum_required(VERSION 3.20)
project(algo)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") 
include(use-go)
include(use-clang)

use_clang()

file(
  GLOB_RECURSE bins
  RELATIVE ${CMAKE_SOURCE_DIR}
  "src/*.cpp")
message("==========")
foreach(bin IN LISTS bins)
  cmake_path(GET bin STEM bin_name)
  message(STATUS "+cpp-bin: ${bin_name} <- ${bin}")
  add_executable(${bin_name} "${CMAKE_SOURCE_DIR}/${bin}")
endforeach()
message("==========")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

add_subdirectory(go)
