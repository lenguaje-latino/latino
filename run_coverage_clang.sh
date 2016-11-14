cd bin
./latino ../ejemplos/coverage.lat
llvm-cov gcov ../src/*.c --object-directory ../src/CMakeFiles/latino.dir/
bash <(curl -s https://codecov.io/bash) -t b67d6931-675c-4437-879b-2e1e6e3454d0
cd ..
