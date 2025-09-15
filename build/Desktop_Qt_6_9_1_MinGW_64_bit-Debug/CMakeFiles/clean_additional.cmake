# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ElevatorSimQt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ElevatorSimQt_autogen.dir\\ParseCache.txt"
  "ElevatorSimQt_autogen"
  )
endif()
