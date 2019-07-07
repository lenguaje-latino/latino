#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(regex,2.7,gnuwin32@users.sourceforge.net)
AC_CONFIG_SRCDIR([src/regex.c])
AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE(regex,2.7)

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h langinfo.h libintl.h limits.h locale.h stdint.h stdlib.h string.h unistd.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_INT32_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_MBRTOWC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([clock_gettime isascii memmove memset nl_langinfo re_comp regcomp setlocale stpcpy strcasecmp strchr])

AC_CONFIG_FILES([Makefile
				doc/Makefile
				src/Makefile
				testsuite/Makefile
			])

AC_OUTPUT
