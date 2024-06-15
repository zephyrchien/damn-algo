macro(use_clang)
  find_program(clang_bin clang++ PATHS)
  if(clang_bin)
    string(REPLACE "/bin/clang++" "" clang_home "${clang_bin}")
    message(STATUS "cpp-sdk: ${clang_home}")
  else()
    message(FATAL_ERROR "cant find clang++")
  endif()

  execute_process(
    COMMAND "${clang_bin}" -print-target-triple
    OUTPUT_VARIABLE clang_target_triple
    OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ERROR_IS_FATAL ANY)
  if(NOT clang_target_triple)
    message(FATAL_ERROR "cant use clang++")
  endif()

  set(CMAKE_CXX_COMPILER "${clang_bin}")
  set(CMAKE_CXX_STANDARD 23)
  set(CMAKE_CXX_STANDARD_REQUIRED 23)

  set(clang_incs "${clang_home}/include/c++/v1")
  set(clang_libs "${clang_home}/lib/${clang_target_triple}")
  message(STATUS "cpp-inc: ${clang_incs}")
  message(STATUS "cpp-lib: ${clang_libs}")
  set(CMAKE_BUILD_RPATH "${clang_libs}")
  include_directories(${clang_incs} ${CMAKE_SOURCE_DIR})
  link_directories(${clang_libs})
endmacro()
