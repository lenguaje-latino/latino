#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

infodir = $(exec_prefix)/info
inst_infodir = $(infodir)

info_TEXINFOS = regex.texi

mandir = $(exec_prefix)/man
inst_mandir = $(mandir)

man_MANS = \
regex.h.0p \
regcomp.3 \
regcomp.3p \
regerror.3 \
regerror.3p \
regex.3 \
regex.7 \
regexec.3 \
regexec.3p \
regfree.3 \
regfree.3p

regex.texi: @srcdir@/xregex.texi @srcdir@/../src/regex.h
	awk -f @srcdir@/include.awk -v source=@srcdir@/../src/regex.h \
		< @srcdir@/xregex.texi | expand >$@
