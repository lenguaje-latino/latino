#!/bin/bash

flex latlex.l
bison -y latparse.y
cp *.c ../../src
cp *.h ../../src
