
SET ( BOOST_VERSION 1.57.0 )
string( REPLACE "." "_" BOOST_VERSION_UNDERSCORE ${BOOST_VERSION} )

if(NOT DEFINED use_bat)
  if(WIN32)
    set(use_bat 1)
  else()
    set(use_bat 0)
  endif()
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(am 64)
else()
  set(am 32)
endif()

set(boost_with_args
  --with-date_time
  --with-filesystem
  --with-iostreams
  --with-program_options
  --with-system
  --with-regex
  --with-chrono
)

if(use_bat)
  set(_toolset "msvc-12.0")

  list(APPEND boost_with_args
    "--layout=tagged" "toolset=${_toolset}")

  set(boost_cmds
    CONFIGURE_COMMAND bootstrap.bat
    BUILD_COMMAND b2 address-model=${am} ${boost_with_args}
    INSTALL_COMMAND b2 address-model=${am} ${boost_with_args}

	--prefix=<INSTALL_DIR> install
  )
else()
  set(boost_cmds
    CONFIGURE_COMMAND ./bootstrap.sh --prefix=<INSTALL_DIR>
    BUILD_COMMAND ./b2 address-model=${am} ${boost_with_args}
    INSTALL_COMMAND ./b2 address-model=${am} ${boost_with_args}
      install
  )
endif()

ExternalProject_Add(
	boost
    PREFIX  ${CMAKE_DEPENDENCY_PATH}/build/boost
	URL http://downloads.sourceforge.net/project/boost/boost/${BOOST_VERSION}/boost_${BOOST_VERSION_UNDERSCORE}.zip
	# URL_MD5 854dcbbff31b896c85c38247060b7713
	INSTALL_DIR ${CMAKE_DEPENDENCY_PATH}/boost
    ${boost_cmds}
    BUILD_IN_SOURCE 1
)

ExternalProject_Get_Property(boost install_dir)
set(BOOST_ROOT "${install_dir}" CACHE INTERNAL "")

list(APPEND BOOTSTRAP_THIRDPARTYLIBS_ARGS
	"-DBOOST_ROOT:PATH=${BOOST_ROOT}"
	"-DBoost_INCLUDE_DIR:PATH=${BOOST_ROOT}/include"
	"-DBOOST_LIBRARYDIR:PATH=${BOOST_ROOT}/lib"
	"-DBoost_NO_SYSTEM_PATHS:BOOL=ON"
	"-DBoost_USE_STATIC_LIBS=ON"
    )
  
