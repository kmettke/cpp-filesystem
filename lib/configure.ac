AC_INIT([libhynodeva-components-cpp-filesystem-sample], [0.1a], [software@mettke.eu], [libhynodeva-components-cpp-filesystem-sample], [https://mettke.eu])

AC_PREREQ([2.59])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([1.10 no-define])
AC_CONFIG_HEADERS([acconfig.h])
AC_CONFIG_MACRO_DIRS([m4])

MYCXXVERSION="c++2a"

AC_SUBST(MYCXXVERSION)


AC_ARG_WITH([c++-version],
  [AS_HELP_STRING([--c++-version=c++2a],[specify c++ flavor [default=c++2a]])],
  [dispatch_cpp_variant=${withval}],
  [dispatch_cpp_variant=c++2a]
  )
AS_CASE([$dispatch_cpp_variant],
  [c++2a],[
	  MYCXXVERSION="c++2a"
  ],
  [AC_MSG_ERROR("invalid c++-variant $dispatch_cpp_variant")]
)
AC_ARG_WITH([build-variant],
  [AS_HELP_STRING([--with-build-variant=release|debug|releaseassert|releasedebuginfo], [Specify build variant [default=release]])],
  [dispatch_build_variant=${withval}],
  [dispatch_build_variant=debug]
)
AS_CASE([$dispatch_build_variant],
  [debug], [
    default_compiler_flags="-g -O0 -Wall -D__DEBUG__"
    dispatch_enable_asserts=true
    dispatch_enable_optimization=false
  ],
  [release], [
    default_compiler_flags="-O2"
    dispatch_enable_asserts=false
    dispatch_enable_optimization=true
  ],
  [releaseassert], [
    default_compiler_flags="-O2"
    dispatch_enable_asserts=true
    dispatch_enable_optimization=true
  ],
  [releasedebuginfo], [
    default_compiler_flags="-g -O2"
    dispatch_enable_asserts=false
    dispatch_enable_optimization=true
  ],
  [AC_MSG_ERROR("invalid build-variant $dispatch_build_variant")]
)
AM_CONDITIONAL(DISPATCH_ENABLE_ASSERTS, $dispatch_enable_asserts)
AM_CONDITIONAL(DISPATCH_ENABLE_OPTIMIZATION, $dispatch_enable_optimization)




AC_ARG_ENABLE([useopenmp],
[  --enable-openmp    Turn on OpenMP Optimization],
[case "${enableval}" in
  yes) usegomp=true ;;
  no)  usegomp=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-openmp]) ;;
esac],[usegomp=true])

AM_CONDITIONAL([USEOPENMP], [test x$usegomp = xtrue])









MULTITHREAD_CXX=""
if test x$usegomp = xtrue ; then
  MULTITHREAD_CXX="$MULTITHREAD_CXX -fopenmp"
  AC_MSG_NOTICE("Using -fopenmp Flag for Automatic Multithreading")
fi
CXXFLAGS="$CXXFLAGS $default_compiler_flags -fpermissive -std=$MYCXXVERSION $MULTITHREAD_CXX"
SQLCXXFLAGS="$CXXFLAGS $default_compiler_flags -fpermissive -std=$MYCXXVERSION "
LDFLAGS="$LDFLAGS -ldl"
SQLLDFLAGS="$LDFLAGS -ldl"
CFLAGS="$CFLAGS $default_compiler_flags -fpermissive -std=$MYCXXVERSION $MULTITHREAD_CXX"
SQLCFLAGS="$CFLAGS $default_compiler_flags -fpermissive -std=$MYCXXVERSION "
ARFLAGS="$ARFLAGS"
AC_SUBST(CXXFLAGS)
AC_SUBST(SQLCXXFLAGS)
AC_SUBST(CFLAGS)
AC_SUBST(LDFLAGS)
#AC_SUBST(ARFLAGS)
#AC_SUBST(LIBADD)
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_PROG_INSTALL
AC_PREFIX_DEFAULT("/usr/local")
# Checks for library functions.
AC_CHECK_FUNCS([gethostbyname memset socket bind])
AC_PROG_RANLIB
#AM_PROG_AR
#AC_ENABLE_SHARED
#AC_PROG_LIBTOOL(libtool)
LT_INIT


AC_PROG_CXX(g++)


AC_CONFIG_FILES([Makefile ])
#AC_CONFIG_SUBDIRS([])
AC_OUTPUT
