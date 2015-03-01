
call "%VS120COMNTOOLS%..\\..\\VC\\vcvarsall.bat" x86_amd64

mkdir build
mkdir build\deps
cd build\deps

cmake -DMAIN_BUILD_TYPE=relwithdebinfo -DMAIN_PROJECT_GENERATOR="Visual Studio 12 2013 Win64" -G "NMake Makefiles" ../../bootstrap
nmake


cd ..
cd ..