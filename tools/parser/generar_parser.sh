#!/bin/bash
flex latlex.l
bison -y latparse.y
<<<<<<< HEAD
cp *.c ../../src
# cp *.h ../../src
cp *.h ../../include
=======
mv *.c ../../src
mv *.h ../../include
>>>>>>> 9e7c3d9aa5d238a80d09553b9ceabc7ba57941ca
