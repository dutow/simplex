# Basic compiler flags: warning levels, treat warnings as errors, c++11

IF (CMAKE_COMPILER_IS_GNUCXX)
  SET (CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror -pedantic -pthread")
ENDIF ()

IF (MSVC)
	SET (CMAKE_CXX_FLAGS "/W4 /WX /EHsc")
ENDIF ()