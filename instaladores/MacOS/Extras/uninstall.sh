#!/bin/sh

## Remove Latino-MySQL library

sudo /bin/rm -f /usr/local/bin/latino
sudo /bin/rm -f /usr/local/lib/liblatino.dylib
sudo /bin/rm -f /usr/local/lib/libliblatino_static.a
sudo /bin/rm -f /usr/local/share/man/man1/latino.1.gz
sudo /bin/rm -f /usr/local/share/nano/latino.nanorc
sudo /bin/rm -f /usr/local/share/applications/latino.desktop
sudo /bin/rm -f /usr/local/share/latino/desktop.png
sudo /bin/rm -f /usr/local/include/latino.h
sudo /bin/rm -f /usr/local/include/latast.h
sudo /bin/rm -f /usr/local/include/latcompat.h
sudo /bin/rm -f /usr/local/include/latdic.h
sudo /bin/rm -f /usr/local/include/latdo.h
sudo /bin/rm -f /usr/local/include/latlist.h
sudo /bin/rm -f /usr/local/include/latmem.h
sudo /bin/rm -f /usr/local/include/latmv.h
sudo /bin/rm -f /usr/local/include/latobj.h

exit 0