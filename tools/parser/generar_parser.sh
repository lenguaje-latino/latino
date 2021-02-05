#!/bin/bash
flex latlex.l
bison -y latparse.y
mv *.c ../../src
mv *.h ../../include
