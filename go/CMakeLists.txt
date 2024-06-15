find_program(go_bin go PATHS)
if(go_bin)
  string(REPLACE "/bin/go" "" go_home "${go_bin}")
  message(STATUS "go-sdk: ${go_home}")
else()
  message(FATAL_ERROR "cant find go sdk")
endif()

execute_process(
  COMMAND "${go_bin}" version
  OUTPUT_VARIABLE go_version
  OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ERROR_IS_FATAL ANY)
if(go_version)
  message(STATUS "go-sdk: ${go_version}")
else()
  message(FATAL_ERROR "cant run go sdk")
endif()

file(
  GLOB_RECURSE bins
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  "src/*.go")
message("==========")
foreach(bin IN LISTS bins)
  cmake_path(GET bin STEM bin_name)
  message(STATUS "+go-bin: ${bin_name}-go <- ${bin}")
  add_custom_command(
    OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/${bin_name}-go"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${bin}"
    COMMAND "${go_bin}" build -o
      "${CMAKE_CURRENT_BINARY_DIR}/${bin_name}-go"
      "${CMAKE_CURRENT_SOURCE_DIR}/${bin}"
  )
  add_custom_target(
    "${bin_name}-go" ALL
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${bin_name}-go"
  )
endforeach()
message("==========")

