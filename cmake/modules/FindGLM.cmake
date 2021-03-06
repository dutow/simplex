# Finds the GLM library

if(NOT GLM_PACKAGE_DIR)
	message("ERROR: GLM_PACKAGE_DIR requires to be set")
endif(NOT GLM_PACKAGE_DIR)

set(GLM_INCLUDE_DIR ${GLM_PACKAGE_DIR})
set(GLM_LIBRARY )

include_directories(${GLM_INCLUDE_DIR})

if(GLM_PACKAGE_DIR AND GLM_INCLUDE_DIR)
	set(GLM_FOUND "YES")
    message(STATUS "Found GLM!")
endif(GLM_PACKAGE_DIR AND GLM_INCLUDE_DIR)