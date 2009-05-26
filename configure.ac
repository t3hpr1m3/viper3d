AC_PREREQ([2.63])
AC_INIT([viper3d], [0.1.0], [vmizzle@gmail.com-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([viper3d/RenderSystem.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
m4_defun([_LT_AC_LANG_F77_CONFIG], [:])
m4_defun([_LT_AC_LANG_GCJ_CONFIG], [:])
m4_defun([_LT_AC_LANG_RC_CONFIG], [:])
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL

# Check for tracing
AC_MSG_CHECKING([whether to enable trace output])
AC_ARG_ENABLE(tracing,
	AC_HELP_STRING([--disable-tracing], [turn off trace output]))
if test x"$enable_tracing" = x"no"; then
	AC_MSG_RESULT(no)
else
	AC_MSG_RESULT(yes)
	AC_DEFINE(TRACE_ENABLE, 1, [Define to enable trace output])
fi

# Checks for libraries.
AC_CHECK_LIB([Xxf86vm], [XCreateWindow], [], AC_MSG_ERROR([X not installed.]))
AC_CHECK_LIB([GL], [glXCreateContext], [], AC_MSG_ERROR([OpenGL not available.]))

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday])

AC_CONFIG_FILES([Makefile
                 viper3d/Makefile
                 viper3d/src/Makefile
				 viper3d/math/Makefile
				 viper3d/math/src/Makefile
				 viper3d/util/Makefile
				 viper3d/util/src/Makefile
				 viper3d/render/Makefile
				 viper3d/render/opengl/Makefile
				 test/Makefile
])
AC_OUTPUT
