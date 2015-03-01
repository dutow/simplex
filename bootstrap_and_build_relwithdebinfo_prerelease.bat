
call "%VS120COMNTOOLS%..\\..\\VC\\vcvarsall.bat" x86_amd64

mkdir build
mkdir build\deps
cd build\deps

cmake -DMAIN_BUILD_TYPE=relwithdebinfo -DSIMPLEX_MAGIC_ASSETS="RELEASE" -DBUILD_PRODUCT="TRUE" -DMAIN_PROJECT_GENERATOR="NMake Makefiles" -G "NMake Makefiles" ../../bootstrap
nmake

cd ..
nmake

cd ..