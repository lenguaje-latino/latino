# instalar dependencias
# pacman -S clang cmake mingw-w64-x86_64-toolchain libreadline libreadline-devel

rm -fr build/
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ../..
make
make install
cd ..
