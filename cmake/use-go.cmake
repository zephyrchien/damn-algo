macro(use_go)
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
endmacro()

function(add_go_exe name source)
  add_custom_command(
    OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/${name}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${source}"
    COMMAND "${go_bin}" build -o
      "${CMAKE_CURRENT_BINARY_DIR}/${name}"
      "${CMAKE_CURRENT_SOURCE_DIR}/${source}"
  )
  add_custom_target(
    "${name}" ALL
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${name}"
  )
endfunction()
