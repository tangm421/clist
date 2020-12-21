#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([clist], [1.0.1.1114], [tangm421@outlook.com])
AC_CONFIG_SRCDIR([clist/clist.c])
AC_CONFIG_HEADER(config.h)
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

#m4_pattern_forbid([^PKG_])


AM_INIT_AUTOMAKE
AM_PROG_AR([AC_MSG_ERROR([cannot find any available compression tool for \$AR])])


AC_DISABLE_SHARED
LT_INIT()
# Checks for programs.
AC_PROG_CC
#AC_DISABLE_SHARED

#AC_PROG_INSTALL
#AC_PROG_LIBTOOL
dnl AC_PROG_RANLIB

AC_CANONICAL_HOST

#AC_PROG_MAKE_SET


# Checks for libraries.

# Checks for header files.
#AC_CHECK_HEADERS([malloc.h stdio.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
#AC_CHECK_HEADER_STDBOOL
AC_CHECK_HEADERS_ONCE

AC_CHECK_HEADERS([db_cxx.h],
 [echo "db_cxx.h found"],
 [AC_MSG_WARN([db_cxx.h not found])],
 [#ifdef HAVE_FOO_H
 # include <inttypes.h>
 #endif
 ])

AC_MSG_NOTICE([Using native OSTYPE value from \$host_os: $host_os, ARCH/LARCH value from \$host_cpu: $host_cpu])

#AC_DEFINE(PROJECT_IMPORTEXPORT, [], [Only usefull for windows])
#AH_TEMPLATE(PROJECT_IMPORTEXPORT, [Only usefull for windows])
AC_DEFINE_UNQUOTED(PROJECT_IMPORTEXPORT, ${PROJECT_IMPORTEXPORT:""}, [Only usefull for windows])

# AM_CONDITIONAL(ENABLE_CLIST_DEBUG, false)
# AC_ARG_WITH(clist-debug, 
# [  --enable-clist-debug    enable clist debug info],
 # [AC_DEFINE_UNQUOTED(ENABLE_CLIST_DEBUG, , ENABLE_CLIST_DEBUG)
 # AC_SUBST(LIBCLIST_CPPFLAGS, "-DCLIST_DEBUG")
 # AM_CONDITIONAL(ENABLE_CLIST_DEBUG, true)],
 # [ AC_SUBST(LIBCLIST_CPPFLAGS, "")])

# AM_CONDITIONAL(ENABLE_CLIST_DEBUG, false)
# AC_ARG_ENABLE(clist-debug,
# [  --enable-clist-debug        Enable clist debug print],
 # [AC_DEFINE_UNQUOTED(ENABLE_CLIST_DEBUG, , ENABLE_CLIST_DEBUG)
 # AC_SUBST(LIBCLIST_CPPFLAGS, "-DCLIST_DEBUG")
 # AM_CONDITIONAL(ENABLE_CLIST_DEBUG, true)],
 # [ AC_SUBST(LIBCLIST_CPPFLAGS, "")])

AC_ARG_ENABLE(clist-debug,
[AS_HELP_STRING([--enable-clist-debug], [Enable clist debug print])],
 AC_SUBST(LIBCLIST_CPPFLAGS, "-DCLIST_DEBUG"),
 AC_SUBST(LIBCLIST_CPPFLAGS, ""))


# Checks for library functions.
#AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile clist/Makefile samples/Makefile])
AC_OUTPUT

#AC_OUTPUT([Makefile clist/Makefile samples/Makefile])
