set(EPICS_BASE_ROOT "${CMAKE_SOURCE_DIR}/epics-base")
set(EPICS_BASE_INCLUDE_DIRS "${EPICS_BASE_ROOT}/include")

if(WIN32)
  add_library(Com STATIC IMPORTED)
  set_target_properties(Com PROPERTIES
    IMPORTED_LOCATION
      "${EPICS_BASE_ROOT}/lib/$ENV{EPICS_HOST_ARCH}/${CMAKE_STATIC_LIBRARY_PREFIX}Com${CMAKE_STATIC_LIBRARY_SUFFIX}"
  )
  target_include_directories(Com INTERFACE "${EPICS_BASE_INCLUDE_DIRS}/os/win32")
else()
  add_library(Com SHARED IMPORTED)
  set(EPICS_BASE_LIB_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}Com${CMAKE_SHARED_LIBRARY_SUFFIX}")
  set_target_properties(Com PROPERTIES
    IMPORTED_SONAME
      "${EPICS_BASE_LIB_NAME}"
    IMPORTED_LOCATION
      "${EPICS_BASE_ROOT}/lib/$ENV{EPICS_HOST_ARCH}/${EPICS_BASE_LIB_NAME}.3.25.0"
  )
  target_include_directories(Com INTERFACE "${EPICS_BASE_INCLUDE_DIRS}/os/Linux")
endif()
target_include_directories(Com INTERFACE "${EPICS_BASE_INCLUDE_DIRS}")
if(MSVC)
  target_include_directories(Com INTERFACE "${EPICS_BASE_INCLUDE_DIRS}/compiler/msvc")
else()
  target_include_directories(Com INTERFACE "${EPICS_BASE_INCLUDE_DIRS}/compiler/gcc")
endif()
