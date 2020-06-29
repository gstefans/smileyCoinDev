FreeBSD build guide
====================
(Tested on FreeBSD 12.1)

This guide describes how to build smileycoind and command-line utilities on FreeBSD.

This guide does not contain instructions for building the GUI.

Preparation
---------------------
You will need the following dependencies, which can be installed as root via pkg:

    pkg install autoconf automake boost-libs git gmake libevent libtool pkgconf openssl db5
    git clone https://github.com/tutor-web/smileyCoin.github

See [build-unix.md](build-unix.md) for a complete overview of dependencies.

### Building SmileyCoin

```bash
./autogen.sh
./configure LDFLAGS="$LDFLAGS -L/usr/local/lib/db5/" \
            CPPFLAGS="$CPPFLAGS -I/usr/local/include/db5/" \
            MAKE=gmake \
            CC=`which cc` \
            CXX=`which c++` \
            --with-gui=no \
gmake -j $(sysctl hw.ncpu | awk -F: '{print $2}')
```
