cmake_minimum_required(VERSION 3.20)
project(algo)

find_program(clang_bin clang++ PATHS)
if(clang_bin)
  string(REPLACE "/bin/clang++" "" clang_home "${clang_bin}")
  message(STATUS "sdk: ${clang_home}")
else()
  message(FATAL_ERROR "cant find clang++")
endif()

execute_process(
  COMMAND "${clang_bin}" -print-target-triple
  OUTPUT_VARIABLE clang_target_triple
  OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ERROR_IS_FATAL ANY)
if(NOT clang_target_triple)
  message(FATAL_ERROR "cant find target")
endif()

set(CMAKE_CXX_COMPILER "${clang_bin}")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

set(clang_incs "${clang_home}/include/c++/v1")
set(clang_libs "${clang_home}/lib/${clang_target_triple}")
message(STATUS "inc: ${clang_incs}")
message(STATUS "lib: ${clang_libs}")
set(CMAKE_BUILD_RPATH "${clang_libs}")
include_directories(${clang_incs} ${CMAKE_SOURCE_DIR})
link_directories(${clang_libs})

file(
  GLOB_RECURSE bins
  RELATIVE ${CMAKE_SOURCE_DIR}
  "src/*.cpp")
message("==========")
foreach(bin IN LISTS bins)
  cmake_path(GET bin STEM bin_name)
  message(STATUS "+bin: ${bin_name} <- ${bin}")
  add_executable(${bin_name} "${CMAKE_SOURCE_DIR}/${bin}")
endforeach()
message("==========")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
