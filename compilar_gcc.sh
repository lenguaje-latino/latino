rm -f CMakeCache.txt
export CC=gcc
export CXX=g++
export CMAKE_C_COMPILER=gcc
export CMAKE_CXX_COMPILER=g++
cmake -G "Unix Makefiles" .
make clean
make
