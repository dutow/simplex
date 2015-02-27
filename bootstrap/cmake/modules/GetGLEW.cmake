
# download binary on windwows... TODO other platforms
# http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0-win32.zip/download



ExternalProject_Add(
    glew
    PREFIX ${CMAKE_DEPENDENCY_PATH}/build/glew
    URL http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0-win32.zip/download
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
	INSTALL_DIR ${CMAKE_DEPENDENCY_PATH}/glew
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory "<SOURCE_DIR>/include" "<INSTALL_DIR>/include"
	COMMAND	 ${CMAKE_COMMAND} -E copy_directory "<SOURCE_DIR>/lib/Release/x64" "<INSTALL_DIR>/lib"
    LOG_DOWNLOAD ON
    )
	
ExternalProject_Get_Property( glew install_dir )
set(GLEW_ROOT "${install_dir}" CACHE INTERNAL "")

list(APPEND BOOTSTRAP_THIRDPARTYLIBS_ARGS
	"-DGLEW_INCLUDE_DIR:PATH=${GLEW_ROOT}/include"
	"-DGLEW_LIBRARY:PATH=${GLEW_ROOT}/lib/glew32s.lib"
    )
