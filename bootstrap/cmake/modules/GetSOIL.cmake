
# a github form with cmake:
# https://github.com/paralin/soil



ExternalProject_Add(
    soil
    PREFIX ${CMAKE_DEPENDENCY_PATH}/build/soil
    GIT_REPOSITORY https://github.com/paralin/soil.git
	INSTALL_DIR ${CMAKE_DEPENDENCY_PATH}/soil
	INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/inc <INSTALL_DIR>/include
	COMMAND ${CMAKE_COMMAND} -E copy <BINARY_DIR>/soil.lib <INSTALL_DIR>/lib/soil.lib
    LOG_DOWNLOAD ON
    )
	
ExternalProject_Get_Property( soil install_dir )
set(SOIL_ROOT "${install_dir}" CACHE INTERNAL "")

list(APPEND BOOTSTRAP_THIRDPARTYLIBS_ARGS
	"-DSOIL_INCLUDE_DIR:PATH=${SOIL_ROOT}/include"
	"-DSOIL_LIBRARIES:PATH=${SOIL_ROOT}/lib/soil.lib"
    )
