Welcome to PDCursesMod!
=======================

Public Domain Curses, aka PDCursesMod, is an implementation of X/Open
curses for multiple platforms. Relative to the ['official' PDCurses
project](https://www.github.com/wmcbrine/PDCurses),  this has a variety of improvements,  adding Windows GUI,
VT-like console,  DOSVGA,  and Plan 9 "flavors" of Curses and expanding
the capabilities of the other flavors (SDL1,  SDL2,  X11, Win32 console,
OS/2, and DOS).  Some details and screen shots at

https://www.projectpluto.com/win32a.htm

Much of this was done during a long period in which the 'official'
PDCurses  was inactive.  Since then,  that version has again been
somewhat active;  most improvements made there have been taken into
this project,  and some improvements from here have gone into PDCurses.
Most programs that compile and run with PDCurses or ncurses will also
compile with PDCursesMod,  and vice versa, as long as you stick to the
(substantial) subset of common functionality. However,  the split
appears to be permanent.

Legal Stuff
-----------

The core package is in the public domain, but small portions of PDCursesMod
are subject to copyright under various licenses.  Each directory contains a
README file, with a section titled "Distribution Status" which describes
the status of the files in that directory.

If you use PDCursesMod in an application, an acknowledgement would be
appreciated, but is not mandatory. If you make corrections or
enhancements to PDCursesMod, please forward them to the current maintainer
for the benefit of other users.

This software is provided AS IS with NO WARRANTY whatsoever.

Ports
-----

PDCurses has been ported to DOS, OS/2, Win32, X11 and SDL1 and SDL2.
PDCursesMod adds DOSVGA,  Windows GUI,  Plan 9,  and VT-like console
ports. A directory containing the port-specific source files exists
for each of these platforms.

Build instructions are in the README file for each platform:

-  [DOS](dos/README.md) for use on DOS
-  [DOSVGA](dosvga/README.md) for use on DOS in graphical modes
-  [OS/2](os2/README.md) for use on OS/2
-  [Plan9](plan9/README.md) for use on Plan9 (APE)
-  [SDL 1.x](sdl1/README.md) for use as separate SDL version 1 window
-  [SDL 2.x](sdl2/README.md) for use as separate SDL version 2 window
-  [wincon](wincon/README.md) (formerly win32) for use on Windows Console
-  [WinGUI](wingui/README.md) for use on Windows Graphics Mode
-  [X11](x11/README.md) (also called XCurses) for use as separate X11 window
-  [VT](vt/README.md) for use on terminal

Distribution Status
-------------------

All files in this directory except configure, config.guess and
config.sub are released to the Public Domain. config.guess and
config.sub are under the GPL; configure is under a free license
described within it.

Build Status
-------------------

PDCursesMod is automatically build in multiple environments:

[![Build status Travis-CI](https://api.travis-ci.com/Bill-Gray/PDCursesMod.svg?branch=master)](https://travis-ci.com/Bill-Gray/PDCurses)
, also providing artifacts: [![Build status Appveyor](https://ci.appveyor.com/api/projects/status/github/Bill-Gray/PDCurses?branch=master&svg=true)](https://ci.appveyor.com/project/Bill-Gray/PDCurses)


Maintainer
----------

Bill Gray
p&#x202e;&ocirc;&#xe7;.&ouml;tulp&#x165;c&eacute;j&ocirc;&#x159;p&#x40;ot&uacute;l&#x202c;m
