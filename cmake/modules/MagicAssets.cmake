
MACRO ( MagicAssets )
	IF ( SIMPLEX_MAGIC_ASSETS EQUAL "RELEASE")
		SET ( SIMPLEX_MAGIC_ASSET_LOCATION "." )
	ELSE ()
		SET ( SIMPLEX_MAGIC_ASSET_LOCATION "${PROJECT_SOURCE_DIR}/assets/${BUILD_SCOPE}" )
	ENDIF ()
		
	CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/src/simplex/config.hpp.in config.hpp )
ENDMACRO ()