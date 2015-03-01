Simplex
=======

As "in the far future, this might be a simple opengl framework".

Features
--------

* Window creation / handling (currntly only windows)
* Event handlers
* Shaders
* One example application rendering newton fractals with a fragment shader
* Automatic building of dependencies

Plans
-----

* Crossplatform support (linux, osx, android ios)
* More abstractions and helpers
* Better documentation

Requirments
-----------

CMake. And some other libs, downloaded and built automatically:

* boost
* glew
* glm
* easylogging

How to build
------------

The repository contains two batch files: 

`bootstrap_relwithdebinfo_develop.bat` builds the projects' dependencies and creates a 
Visual Studio solution for the project itself inside the build directory.

`bootstrap_and_build_relwithdebinfo_prerelease.bat` builds the dependencies and the project 
itself using nmake, and creates a zip containing everything.

For building without the bootstrap script, see the documentation of the Find* cmake scripts 
and provide the neccessary cmake parameters.