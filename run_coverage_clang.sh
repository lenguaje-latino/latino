cd bin
./latino ../ejemplos/coverage.lat
llvm-cov gcov ../src/*.c --object-directory ../src/CMakeFiles/latino.dir/
bash <(curl -s https://codecov.io/bash) -t 4b38427d-b15b-42ce-a276-ce8116c385c4
cd ..
