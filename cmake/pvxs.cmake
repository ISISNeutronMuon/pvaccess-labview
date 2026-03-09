set(PVXS_ROOT "${CMAKE_SOURCE_DIR}/pvxs")

add_library(pvxs STATIC IMPORTED)
target_include_directories(pvxs INTERFACE "${PVXS_ROOT}/include")
set_target_properties(pvxs PROPERTIES
  IMPORTED_LOCATION "${PVXS_ROOT}/lib/$ENV{EPICS_HOST_ARCH}/${CMAKE_STATIC_LIBRARY_PREFIX}pvxs${CMAKE_STATIC_LIBRARY_SUFFIX}"
)

add_library(event_core STATIC IMPORTED)
set_target_properties(event_core PROPERTIES
  IMPORTED_LOCATION "${PVXS_ROOT}/bundle/usr/$ENV{EPICS_HOST_ARCH}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}event_core${CMAKE_STATIC_LIBRARY_SUFFIX}"
)
