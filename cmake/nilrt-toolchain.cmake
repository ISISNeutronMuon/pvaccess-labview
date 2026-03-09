set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(NILRT_SYSROOT /usr/local/oecore-x86_64/sysroots)

set(CMAKE_C_COMPILER ${NILRT_SYSROOT}/x86_64-nilrtsdk-linux/usr/bin/x86_64-nilrt-linux/x86_64-nilrt-linux-gcc)
set(CMAKE_CXX_COMPILER ${NILRT_SYSROOT}/x86_64-nilrtsdk-linux/usr/bin/x86_64-nilrt-linux/x86_64-nilrt-linux-g++)

set(CMAKE_SYSROOT ${NILRT_SYSROOT}/core2-64-nilrt-linux)
set(CMAKE_<LANG>_STANDARD_INCLUDE_DIRECTORIES ${NILRT_SYSROOT}/core2-64-nilrt-linux/usr/include/c++/11.3.0 ${toolchainpath}/core2-64-nilrt-linux/usr/include/c++/11.3.0/x86-64-nilrt-linux)

set(CMAKE_<LANG>_FLAGS "-Wall -fmessage-length=0")
set(CMAKE_<LANG>_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_<LANG>_FLAGS_RELEASE "-O3")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
