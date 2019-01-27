rm -f CMakeCache.txt
export CC=clang
export CXX=clang++
export CMAKE_C_COMPILER=clang
export CMAKE_CXX_COMPILER=clang++
#cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" .
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" .
make clean
make
make install
