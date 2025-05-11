# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Fichaje_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Fichaje_autogen.dir\\ParseCache.txt"
  "Fichaje_autogen"
  )
endif()
