#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

TESTS = $(check_PROGRAMS) $(REGEXTESTS)
REGEXTESTS =

AM_CPPFLAGS = -I../src -I@srcdir@/../src

LIBS = -L../src -lregex
EXEEXT = 

check_PROGRAMS = \
bug-regex1 \
bug-regex2 \
bug-regex3 \
bug-regex4 \
bug-regex6 \
bug-regex7 \
bug-regex8 \
bug-regex9 \
bug-regex10 \
bug-regex11 \
bug-regex12 \
bug-regex13 \
bug-regex14 \
bug-regex16 \
bug-regex17 \
bug-regex18 \
bug-regex21 \
bug-regex22 \
bug-regex23 \
bug-regex25 \
bug-regex26 \
bug-regex27 \
bug-regex28 \
runtests \
runptests 

#bug-regex5 \
bug-regex15 \
bug-regex19 \
bug-regex20 \
bug-regex24 \
regexbug1 \
tst-regex \
tst-regex2 \
tst-regexloc

TESTS_ENVIRONMENT = \
  CU_TEST_NAME=`basename $(abs_srcdir)`,$$tst \
  PATH="../src/.libs$(PATH_SEPARATOR)$$PATH"

# automake makes `check' depend on $(TESTS).  Declare
# dummy targets for $(TESTS) so that make does not complain.

.PHONY: $(REGEXTESTS)
$(REGEXTESTS):
