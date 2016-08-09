cd bin
./latino ../ejemplos/coverage.lat
gcov ../src/*.c --object-directory ../src/CMakeFiles/latino.dir/
bash <(curl -s https://codecov.io/bash)
cd ..
