
ExternalProject_Add(
    easylogging
    PREFIX ${CMAKE_DEPENDENCY_PATH}/build/easylogging
    GIT_REPOSITORY https://github.com/easylogging/easyloggingpp.git
    GIT_TAG "v9.80"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
	INSTALL_DIR ${CMAKE_DEPENDENCY_PATH}/easylogging
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/src <INSTALL_DIR>/include
    LOG_DOWNLOAD ON
    )
	
ExternalProject_Get_Property( easylogging install_dir )
set(EASYLOGGING_ROOT "${install_dir}" CACHE INTERNAL "")

list(APPEND BOOTSTRAP_THIRDPARTYLIBS_ARGS
	"-DEASYLOGGING_PACKAGE_DIR:PATH=${EASYLOGGING_ROOT}/include"
    )
