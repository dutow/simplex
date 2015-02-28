# Groups the source files based on their filesystem folders in visual studio
# Based on: http://cmake.3232098.n2.nabble.com/Keep-folder-structure-in-Visual-Studio-Project-generated-with-CMake-td7586044.html

MACRO (GroupInVisualStudio)
	GroupSources (${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
	GroupSources_HPP (${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
ENDMACRO (GroupInVisualStudio)

MACRO (GroupSources rootdir curdir)
	FILE( GLOB children RELATIVE ${curdir} ${curdir}/*)
	
	FOREACH (child ${children})
		IF(IS_DIRECTORY ${curdir}/${child})
			GroupSources(${rootdir} ${curdir}/${child})
		ELSE ()
			STRING (REPLACE ${rootdir} "Source" groupname ${curdir})
			STRING (REPLACE "/" "\\" groupname ${groupname})
			STRING (REPLACE "\\." "" groupname ${groupname})
			SOURCE_GROUP (${groupname} FILES ${curdir}/${child})
		ENDIF ()
	ENDFOREACH ()
ENDMACRO ()

# TODO: refactor
MACRO (GroupSources_HPP rootdir curdir)
	FILE( GLOB children RELATIVE ${curdir} ${curdir}/*)
	
	FOREACH (child ${children})
		IF(IS_DIRECTORY ${curdir}/${child})
			GroupSources_HPP(${rootdir} ${curdir}/${child})
		ENDIF ()
	ENDFOREACH ()
	
	FILE( GLOB children RELATIVE ${curdir} ${curdir}/*.hpp)
	
	FOREACH (child ${children})
		STRING (REPLACE ${rootdir} "Source" groupname ${curdir})
		STRING (REPLACE "/" "\\" groupname ${groupname})
		STRING (REPLACE "\\." "" groupname ${groupname})
		SOURCE_GROUP (${groupname} FILES ${curdir}/${child})
	ENDFOREACH ()
ENDMACRO ()
