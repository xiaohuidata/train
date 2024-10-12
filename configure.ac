#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([train], [1.0], [xiaosh@channelsoft.com])
AM_INIT_AUTOMAKE(train, 1.0)
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_HEADER_MAJOR
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_STRTOD
AC_CHECK_FUNCS([dup2 floor memmove memset mkdir sqrt strerror strtol strtoul strtoull])

AC_MSG_CHECKING([for gcc version >= 4.8])
gcc_version=`gcc --version | head -n 1 | awk '{print $3}'`
gcc_major=`echo $gcc_version | cut -d. -f1`
gcc_minor=`echo $gcc_version | cut -d. -f2`
if test "$gcc_major" -gt 4 || ( test "$gcc_major" -eq 4 && test "$gcc_minor" -ge 8 ); then
  AC_MSG_RESULT([yes])
  # 可以在这里设置变量或执行其他操作
else
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([gcc version $gcc_version, need 4.8 or greater is required])
fi

PROTOC_FORMATTER="formatter/formatter1"

AC_MSG_CHECKING([for protoc])
if protoc --version > /dev/null 2>&1; then
  protoc_version=`protoc --version | head -n 1 | awk '{print $2}'`
  protoc_magor=`echo $protoc_version | cut -d. -f1`
  protoc_minor=`echo $protoc_version | cut -d. -f2`
  AC_MSG_RESULT([yes] version "$protoc_version")
  if test "$protoc_magor" -gt 3 || ( test "$protoc_magor" -eq 3 && test "$protoc_minor" -ge 22); then
    PROTOC_FORMATTER="formatter/formatter2"
  else
    PROTOC_FORMATTER="formatter/formatter1"
  fi
else
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([no protoc])
fi

AC_SUBST(PROTOC_FORMATTER)

PROTOBUF_PATH="lib/grpc-1.33_dynamic"
AC_ARG_WITH([protobuf_path], [ [--with-protobuf_path=DIR grpc/protoc/protobuf include path [default: lib/grpc-1.33_dynamic]]],
  [
    # 检查用户是否指定了 --with-protobuf_path 选项
    if test "${with_protobuf_path+set}" = set; then
      # 用户指定了 --with-protobuf_path，使用提供的路径
      PROTOBUF_PATH="$with_protobuf_path"
    else
      # 用户没有指定 --with-protobuf_path 选项，使用默认值
      PROTOBUF_PATH="$PROTOBUF_PATH"
    fi
    # 可以在这里添加额外的验证逻辑，例如检查目录是否存在
    if test ! -d "$PROTOBUF_PATH"; then
      AC_MSG_ERROR([directory "$PROTOBUF_PATH" does not exist])
    fi
  ]
)
AC_SUBST(PROTOBUF_PATH)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
