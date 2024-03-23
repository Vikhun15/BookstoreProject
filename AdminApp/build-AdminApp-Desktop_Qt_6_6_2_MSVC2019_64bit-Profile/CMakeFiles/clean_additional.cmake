# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "AdminApp_autogen"
  "CMakeFiles\\AdminApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AdminApp_autogen.dir\\ParseCache.txt"
  )
endif()
