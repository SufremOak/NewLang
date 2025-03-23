AC_INIT([newlang-base], [0.0.2])
AC_CONFIG_SRCDIR([basecompiler.cc])

# Checks for programs.
AC_PROG_CXX
AC_LANG([C++])

# Check for LLVM
AX_LLVM([3.5], [optional]) # Specify minimum required version, optional indicates failure isn't fatal

# Check for specific LLVM components (optional, based on your needs)
# For example:
# AX_LLVM_COMPONENT_X86
# AX_LLVM_COMPONENT_ANALYSIS
# ...

# Check for libraries
# For example:
# AC_CHECK_LIB([z], [compress])

# Check for header files.
AC_CHECK_HEADERS([iostream])

# Check for typedefs, structures, and compiler characteristics.
# For example:
# AC_TYPE_SIZE_T

# Check for library functions.
# For example:
# AC_CHECK_FUNCS([printf sqrt])

# Check for C++11 support (adjust if you need a different standard)
AX_CXX_COMPILE_STDCXX([14], [noext], [mandatory]) # Or use AX_CXX_COMPILE_STDCXX_11 if available


# Handle LLVM availability
AS_IF([test "x$llvm_config" != "x"],
    [
        AC_MSG_NOTICE([Found LLVM])
        LLVM_CPPFLAGS=`$llvm_config --cppflags`
        LLVM_LDFLAGS=`$llvm_config --ldflags --libs all` # Or list specific libraries
        AC_SUBST([LLVM_CPPFLAGS])
        AC_SUBST([LLVM_LDFLAGS])
    ],
    [
        AS_IF([test "x$enable_llvm" != "xno"],
            [
                AC_MSG_ERROR([LLVM is required but not found. Use --disable-llvm to build without it or provide llvm-config in your PATH.])
            ],
            [
                AC_MSG_NOTICE([Building without LLVM support (disabled).])
                AC_DEFINE([WITHOUT_LLVM], [1], [Define to 1 if LLVM is not available])
            ]
        )
    ]
)


AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
