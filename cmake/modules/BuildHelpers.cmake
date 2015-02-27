# 
# Helper functions for the cmake build process to build executables or static libraries
#
# Usage:
#
# MODIFY_SCOPE( name ) in source directories
#
# BUILD_EXECUTABLE( dep1 dep2 dep3 ) for an executable
# BUILD_STATIC_LIB() to build a static lib
#

MACRO( MODIFY_SCOPE addto )
  IF( NOT BUILD_SCOPE )
    SET ( BUILD_SCOPE ${addto} )
    SET ( BUILD_SCOPEDIR ${addto} )
  ELSE( NOT BUILD_SCOPE )
    SET( BUILD_SCOPE "${BUILD_SCOPE}-${addto}" )
    SET( BUILD_SCOPEDIR "${BUILD_SCOPEDIR}/${addto}" )
  ENDIF( NOT BUILD_SCOPE )
ENDMACRO( MODIFY_SCOPE )

MACRO( BUILD_EXECUTABLE )

  SET( MYLIBS ${LIBS} ${ARGV} )

  FILE( GLOB_RECURSE ${BUILD_SCOPE}-sources *.cpp )
  FILE( GLOB_RECURSE ${BUILD_SCOPE}-headers *.hpp )

  ADD_EXECUTABLE( ${BUILD_SCOPE} ${${BUILD_SCOPE}-sources} ${${BUILD_SCOPE}-headers} )
  TARGET_LINK_LIBRARIES(${BUILD_SCOPE} ${MYLIBS})
  #ADD_DEPENDENCIES( ${BUILD_SCOPE} ${ARGV} )

  GroupInVisualStudio()
  
  # TODO: install it!
  #  INSTALL( FILES ${${BUILD_SCOPE}-headers} DESTINATION "include/${BUILD_SCOPEDIR}" )
  #  INSTALL( TARGETS "${BUILD_SCOPE}" LIBRARY DESTINATION "lib" ARCHIVE DESTINATION "lib" )
ENDMACRO( BUILD_EXECUTABLE )

MACRO( BUILD_STATIC_LIB )
  FILE( GLOB_RECURSE ${BUILD_SCOPE}-sources *.cpp )
  FILE( GLOB_RECURSE ${BUILD_SCOPE}-headers *.hpp )

  ADD_LIBRARY( ${BUILD_SCOPE} ${${BUILD_SCOPE}-sources} ${${BUILD_SCOPE}-headers} )

  GroupInVisualStudio()
  
  # TODO
  #  INSTALL( FILES ${${BUILD_SCOPE}-headers} DESTINATION "include/${BUILD_SCOPEDIR}" )
  #  INSTALL( TARGETS "${BUILD_SCOPE}" LIBRARY DESTINATION "lib" ARCHIVE DESTINATION "lib" )
ENDMACRO( BUILD_STATIC_LIB )