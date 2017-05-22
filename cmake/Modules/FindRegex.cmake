#                                               -*- cmake -*-
#
#  FindRegex.cmake: Try to find Regex
#
#  Copyright (C) 2005-2013 EDF-EADS-Phimeca
#
#  This library is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  along with this library.  If not, see <http://www.gnu.org/licenses/>.
#
#  @author dutka
#  @date   2010-02-04 16:44:49 +0100 (Thu, 04 Feb 2010)
#
#
# - Try to find Regex
# Once done this will define
#
#  REGEX_FOUND - System has Regex
#  REGEX_INCLUDE_DIR - The Regex include directory
#  REGEX_LIBRARIES - The libraries needed to use Regex
#  REGEX_DEFINITIONS - Compiler switches required for using Regex

IF (REGEX_INCLUDE_DIR AND REGEX_LIBRARIES)
   # in cache already
   SET(Regex_FIND_QUIETLY TRUE)
ENDIF (REGEX_INCLUDE_DIR AND REGEX_LIBRARIES)

#IF (NOT WIN32)
#   # use pkg-config to get the directories and then use these values
#   # in the FIND_PATH() and FIND_LIBRARY() calls
#   FIND_PACKAGE(PkgConfig)
#   PKG_CHECK_MODULES(PC_REGEX regex)
#   SET(REGEX_DEFINITIONS ${PC_REGEX_CFLAGS_OTHER})
#ENDIF (NOT WIN32)

FIND_PATH(REGEX_INCLUDE_DIR regex.h
   HINTS
   ${REGEX_INCLUDEDIR}
   ${PC_LIBXML_INCLUDE_DIRS}
   PATH_SUFFIXES regex
   )

FIND_LIBRARY(REGEX_LIBRARIES NAMES c regex
   HINTS
   ${PC_REGEX_LIBDIR}
   ${PC_REGEX_LIBRARY_DIRS}
   )

INCLUDE(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set REGEX_FOUND to TRUE if 
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Regex DEFAULT_MSG REGEX_LIBRARIES REGEX_INCLUDE_DIR)

MARK_AS_ADVANCED(REGEX_INCLUDE_DIR REGEX_LIBRARIES)
