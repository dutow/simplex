
ExternalProject_Add(
    glm
    PREFIX ${CMAKE_DEPENDENCY_PATH}/build/glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG "0.9.6.0"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
	INSTALL_DIR ${CMAKE_DEPENDENCY_PATH}/glm
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/glm <INSTALL_DIR>/include/glm
    LOG_DOWNLOAD ON
    )
	
ExternalProject_Get_Property( glm install_dir )
set(GLM_ROOT "${install_dir}" CACHE INTERNAL "")

list(APPEND BOOTSTRAP_THIRDPARTYLIBS_ARGS
	"-DGLM_PACKAGE_DIR:PATH=${GLM_ROOT}/include"
    )
