# libmodbus package version number, (as distinct from shared library version)
# An odd micro number indicates in-progress development from Git
# An even micro number indicates a released version
#
# Making a point release:
# - increase libmodbus_version_micro to the next even number
#
# After the release:
# - increase libmodbus_version_minor to the next odd number
#
# Take care to update the libtool versioning when required (LIBMODBUS_LD_*).
# http://www.gnu.org/software/libtool/manual/html_node/Libtool-versioning.html
#
m4_define([libmodbus_version_major], [3])
m4_define([libmodbus_version_minor], [1])
m4_define([libmodbus_version_micro], [11])

m4_define([libmodbus_release_status],
    [m4_if(m4_eval(libmodbus_version_minor % 2), [1], [snapshot], [release])])

m4_define([libmodbus_version],
    [libmodbus_version_major.libmodbus_version_minor.libmodbus_version_micro])

AC_PREREQ([2.63])
AC_INIT([libmodbus],
        [libmodbus_version],
        [https://github.com/stephane/libmodbus/issues],
        [libmodbus],
        [http://libmodbus.org/])
AC_CONFIG_SRCDIR([src/modbus.c])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([check-news foreign 1.11 silent-rules tar-pax subdir-objects])
AC_PROG_CC
AC_USE_SYSTEM_EXTENSIONS
AC_SYS_LARGEFILE
AC_CONFIG_MACRO_DIR([m4])
AM_SILENT_RULES([yes])

LIBMODBUS_VERSION_MAJOR=libmodbus_version_major
LIBMODBUS_VERSION_MINOR=libmodbus_version_minor
LIBMODBUS_VERSION_MICRO=libmodbus_version_micro
LIBMODBUS_VERSION=libmodbus_version
AC_SUBST(LIBMODBUS_VERSION_MAJOR)
AC_SUBST(LIBMODBUS_VERSION_MINOR)
AC_SUBST(LIBMODBUS_VERSION_MICRO)
AC_SUBST(LIBMODBUS_VERSION)

# ABI version
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
LIBMODBUS_LD_CURRENT=6
LIBMODBUS_LD_REVISION=0
LIBMODBUS_LD_AGE=1
LIBMODBUS_LT_VERSION_INFO=$LIBMODBUS_LD_CURRENT:$LIBMODBUS_LD_REVISION:$LIBMODBUS_LD_AGE
AC_SUBST(LIBMODBUS_LT_VERSION_INFO)

AC_CANONICAL_HOST

# OS check
os_win32="false"
os_cygwin="false"
os_qnx="false"
os_sunos="false"
case "${host_os}" in
      *mingw32*)
    os_win32="true"
  ;;
      *nto-qnx*)
    os_qnx="true"
  ;;
      *cygwin*)
    os_cygwin="true"
  ;;
      *solaris*)
    os_sunos="true"
  ;;
esac
AM_CONDITIONAL(OS_WIN32, test "$os_win32" = "true")
AM_CONDITIONAL(OS_QNX, test "$os_qnx" = "true")

m4_pattern_forbid([^LT_INIT])dnl
LT_INIT([disable-static win32-dll pic-only])

AC_CHECK_HEADERS([ \
    arpa/inet.h \
    byteswap.h \
    errno.h \
    fcntl.h \
    limits.h \
    linux/serial.h \
    netdb.h \
    netinet/in.h \
    netinet/ip.h \
    netinet/tcp.h \
    sys/ioctl.h \
    sys/params.h \
    sys/socket.h \
    sys/time.h \
    sys/types.h \
    termios.h \
    time.h \
    unistd.h \
])

# Cygwin defines IPTOS_LOWDELAY but can't handle that flag so it's necessary to
# workaround that problem and Cygwin doesn't define MSG_DONTWAIT.
AC_CHECK_DECLS([__CYGWIN__])

# Check for network function in libnetwork for Haiku
AC_SEARCH_LIBS(accept, network socket)

# Checks for library functions.
AC_CHECK_FUNCS([accept4 gai_strerror getaddrinfo gettimeofday inet_pton inet_ntop select socket strerror strlcpy])

# Required for MinGW with GCC v4.8.1 on Win7
AC_DEFINE(WINVER, 0x0501, _)

# Required for bswap
AC_C_INLINE

# libtool
AC_PROG_CXX

# Various types
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

if test "$os_cygwin" = "false"; then
    # Required for getaddrinfo (TCP IP - IPv6)
    AC_CHECK_HEADERS([winsock2.h], HAVE_WINSOCK2_H=yes)
    if test "x$HAVE_WINSOCK2_H" = "xyes"; then
        LIBS="$LIBS -lws2_32"
    AC_SUBST(LIBS)
    fi
fi

if test "$os_sunos" = "true"; then
    LIBS="$LIBS -lnsl -lsocket"
    AC_SUBST(LIBS)
fi

# Check for RS485 support (Linux kernel version 2.6.28+)
AC_CHECK_DECLS([TIOCSRS485], [], [], [[#include <sys/ioctl.h>]])
# Check for RTS flags
AC_CHECK_DECLS([TIOCM_RTS], [], [], [[#include <sys/ioctl.h>]])

WARNING_CFLAGS="-Wall \
-Wmissing-declarations -Wmissing-prototypes \
-Wnested-externs -Wpointer-arith \
-Wsign-compare -Wchar-subscripts \
-Wstrict-prototypes -Wshadow \
-Wformat-security"
AC_SUBST([WARNING_CFLAGS])

# Build options
AC_ARG_ENABLE(tests,
	AS_HELP_STRING([--disable-tests],
	[Build tests (default: yes)]),,
	[enable_tests=yes])
AM_CONDITIONAL(BUILD_TESTS, [test $enable_tests != no])

AC_CONFIG_HEADERS([config.h tests/unit-test.h])
AC_CONFIG_FILES([
        Makefile
        src/Makefile
        src/modbus-version.h
        src/win32/modbus.dll.manifest
        tests/Makefile
        libmodbus.pc
])

AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
    [Enable debug symbols (default is no)])],
  [enable_debug=$enableval],
  [enable_debug=no])

AS_IF([test "x$enable_debug" = "xyes"], [
  CFLAGS="-g -O0"
  CXXFLAGS="-g -O0"
], [
  CFLAGS="-O2"
  CXXFLAGS="-O2"
])

AC_OUTPUT
AC_MSG_RESULT([
        $PACKAGE $VERSION
        ===============

        prefix:                 ${prefix}
        sysconfdir:             ${sysconfdir}
        libdir:                 ${libdir}
        includedir:             ${includedir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS} ${WARNING_CFLAGS}
        ldflags:                ${LDFLAGS}

        tests:                  ${enable_tests}
])
