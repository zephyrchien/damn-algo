use_go()

file(
  GLOB_RECURSE bins
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  "src/*.go")
message("==========")
foreach(bin IN LISTS bins)
  cmake_path(GET bin STEM bin_name)
  message(STATUS "+go-bin: ${bin_name}-go <- ${bin}")
  add_go_exe("${bin_name}-go" ${bin})
endforeach()
message("==========")

