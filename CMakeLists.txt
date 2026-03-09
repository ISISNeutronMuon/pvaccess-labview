cmake_minimum_required(VERSION 3.12.4)

include(GenerateExportHeader)

cmake_policy(SET CMP0091 NEW)

project(pva_labview
  VERSION 0.1.1
  DESCRIPTION "A PVAccess library for LabVIEW"
  LANGUAGES C CXX
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(labview)
include(epics-base)
include(pvxs)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267 /wd4244")
  add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:REF>")
  add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:ICF>")
  add_compile_definitions(PRIVATE "_UNICODE" "UNICODE")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D'__cdecl=__attribute__((__cdecl__))'")
endif()

add_library(pva_labview SHARED
  src/lv_interop.cpp
  src/exceptions.cpp
  src/server.cpp
  src/client.cpp
  src/value.cpp
)
if(WIN32)
  target_sources(pva_labview PUBLIC "${CMAKE_SOURCE_DIR}/src/dllmain.cpp")
endif()

target_compile_features(pva_labview PRIVATE cxx_std_14)

set_target_properties(pva_labview PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)
if(WIN32)
  set_target_properties(pva_labview PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/labview/libraries/$ENV{EPICS_HOST_ARCH}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/labview/libraries/$ENV{EPICS_HOST_ARCH}"
  )
elseif(LINUX AND NOT NILRT)
  set_target_properties(pva_labview PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/labview/libraries/$ENV{EPICS_HOST_ARCH}"
  )
endif()

# Compiler
target_include_directories(pva_labview PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}" # For the export header
  "./src"
)
if(MSVC)
  # Fixes static linking
  target_compile_options(pva_labview PRIVATE "$<$<CONFIG:Debug>:/MTd>$<$<CONFIG:Release>:/MT>")
endif()

# Linker
if(WIN32)
  find_package(PThreads4W CONFIG REQUIRED)
  target_link_libraries(pva_labview PRIVATE
    PThreads4W::PThreads4W
    Ws2_32.lib
    Netapi32.lib
    Iphlpapi.lib
    DbgHelp.lib
    BCrypt.lib
    labview
    Com
    event_core
    pvxs
  )
  # Module labview.lib is not compatible with the safe exception handling feature
  target_link_options(pva_labview PRIVATE "/SAFESEH:NO")
else()
  target_link_libraries(pva_labview
    -static-libgcc
    Com
    pvxs
  )
endif()

GENERATE_EXPORT_HEADER(pva_labview)

if(NILRT)
  include(Installing)
  include(Packing)
endif()
