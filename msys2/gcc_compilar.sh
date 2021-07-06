# instalar dependencias
# pacman -S gcc cmake mingw-w64-x86_64-toolchain libreadline libreadline-devel

pacman -S gcc 
pacman -S cmake 
pacman -S mingw-w64-x86_64-toolchain 
pacman -S libreadline 
pacman -S libreadline-devel

rm -fr build/
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_BUILD_TYPE=Debug -DMSYS=ON -G "Unix Makefiles" ../..
make
make install
cd ..
