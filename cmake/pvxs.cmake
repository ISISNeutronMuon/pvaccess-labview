set(PVXS_ROOT "${CMAKE_SOURCE_DIR}/pvxs")

if(WIN32)
  add_library(pvxs STATIC IMPORTED)
  set_target_properties(pvxs PROPERTIES
    IMPORTED_LOCATION
      "${PVXS_ROOT}/lib/$ENV{EPICS_HOST_ARCH}/${CMAKE_STATIC_LIBRARY_PREFIX}pvxs${CMAKE_STATIC_LIBRARY_SUFFIX}"
  )

  add_library(event_core STATIC IMPORTED)
  set_target_properties(event_core PROPERTIES
    IMPORTED_LOCATION
      "${PVXS_ROOT}/bundle/usr/$ENV{EPICS_HOST_ARCH}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}event_core${CMAKE_STATIC_LIBRARY_SUFFIX}"
  )
else()
  add_library(pvxs SHARED IMPORTED)
  set(PVXS_LIB_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}pvxs${CMAKE_SHARED_LIBRARY_SUFFIX}")
  set_target_properties(pvxs PROPERTIES
    IMPORTED_SONAME
      "${PVXS_LIB_NAME}"
    IMPORTED_LOCATION
      "${PVXS_ROOT}/lib/$ENV{EPICS_HOST_ARCH}/${PVXS_LIB_NAME}.1.5"
  )
endif()
target_include_directories(pvxs INTERFACE "${PVXS_ROOT}/include")
