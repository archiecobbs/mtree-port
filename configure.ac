#
# mtree - Utility for creating and verifying file hierarchies
# 

AC_INIT([mtree Utility for creating and verifying file hierarchies], [1.0.3], [http://www.freebsd.org/], [mtree])
AC_CONFIG_AUX_DIR(scripts)
AM_INIT_AUTOMAKE
dnl AM_MAINTAINER_MODE
AC_PREREQ(2.59)
AC_PREFIX_DEFAULT(/usr)
AC_PROG_MAKE_SET

[CFLAGS="-g -O3 -pipe -Wall -Waggregate-return -Wcast-align -Wchar-subscripts -Wcomment -Wformat -Wimplicit -Wmissing-declarations -Wmissing-prototypes -Wnested-externs -Wno-long-long -Wparentheses -Wpointer-arith -Wredundant-decls -Wreturn-type -Wswitch -Wtrigraphs -Wuninitialized -Wunused -Wwrite-strings -Wshadow -Wstrict-prototypes -Wcast-qual $CFLAGS"]
AC_SUBST(CFLAGS)

# Compile flags for Linux
AC_DEFINE(_GNU_SOURCE, 1, GNU functions)
AC_DEFINE(_BSD_SOURCE, 1, BSD functions)
AC_DEFINE(_XOPEN_SOURCE, 500, XOpen functions)

# Compile flags for Mac OS
AC_DEFINE(_DARWIN_C_SOURCE, 1, MacOS functions)

# Check for required programs
AC_PROG_INSTALL
AC_PROG_CC

# Check for libcrypto library
AC_CHECK_LIB(crypto, CRYPTO_thread_id,,)

# Check for required header files
AC_HEADER_STDC
AC_CHECK_HEADERS(dirent.h err.h errno.h fcntl.h fnmatch.h fts.h grp.h limits.h pwd.h signal.h stdarg.h stddef.h stdint.h stdio.h stdlib.h string.h time.h unistd.h sys/cdefs.h sys/param.h sys/queue.h sys/stat.h sys/time.h sys/types.h, [],
        [AC_MSG_ERROR([required header file '$ac_header' missing])])

# Check for optional header files
AC_CHECK_HEADERS(openssl/md5.h openssl/sha.h openssl/ripemd.h,,)

# Check for optional functions
AC_CHECK_FUNCS(getmode getline,,)

# Optional features
AC_ARG_ENABLE(Werror,
    AC_HELP_STRING([--enable-Werror],
        [enable compilation with -Werror flag (default NO)]),
    [test x"$enableval" = "xyes" && CFLAGS="${CFLAGS} -Werror"])

# Generated files
AC_CONFIG_FILES(Makefile)
AM_CONFIG_HEADER(config.h)

# Go
AC_OUTPUT
