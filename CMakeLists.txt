cmake_minimum_required(VERSION 3.12.4)

include(GenerateExportHeader)

cmake_policy(SET CMP0091 NEW)

project(pva_labview C CXX)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267 /wd4244")
  add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:REF>")
  add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:ICF>")
  add_compile_definitions(PRIVATE "_UNICODE" "UNICODE")
  if(${CMAKE_GENERATOR_PLATFORM} MATCHES "Win32")
    set(EPICS_HOST_ARCH "win32-x86")
  else()
    set(EPICS_HOST_ARCH "windows-x64")
  endif()
else()
  set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
  set(EPICS_HOST_ARCH "linux-x86_64")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D'__cdecl=__attribute__((__cdecl__))'")
endif()

if(WIN32)
  if(${CMAKE_GENERATOR_PLATFORM} MATCHES "Win32")
    cmake_path(SET LABVIEW_LIB "$ENV{ProgramFiles\(x86\)}/National Instruments/LabVIEW 2021/cintools")
  else()
    cmake_path(SET LABVIEW_LIB "$ENV{ProgramFiles}/National Instruments/LabVIEW 2021/cintools")
  endif()
endif()

find_package(Threads REQUIRED)

# Setup epics-base
set(EPICS_BASE_ROOT "${CMAKE_SOURCE_DIR}/epics-base")
set(EPICS_BASE_INCLUDE_DIRS "${EPICS_BASE_ROOT}/include")
set(EPICS_LIB "${EPICS_BASE_ROOT}/lib/${EPICS_HOST_ARCH}")

# Setup pvxs
set(PVXS_ROOT "${CMAKE_SOURCE_DIR}/pvxs")
set(PVXS_INCLUDE_DIRS "${PVXS_ROOT}/include")
set(PVXS_LIB "${PVXS_ROOT}/lib/${EPICS_HOST_ARCH}")
set(EVENT_LIB "${PVXS_ROOT}/bundle/O.${EPICS_HOST_ARCH}/lib")

add_library(pva_labview SHARED)

target_sources(pva_labview PUBLIC
  src/lv_interop.cpp
  src/exceptions.cpp
  src/server.cpp
  src/client.cpp
  src/value.cpp
)
if(WIN32)
  target_sources(pva_labview PUBLIC src/dllmain.cpp)
endif()

target_compile_features(pva_labview PRIVATE cxx_std_14)

set_target_properties(pva_labview
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../labview/Libraries/${EPICS_HOST_ARCH}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "../labview/Libraries/${EPICS_HOST_ARCH}"
)

# Compiler
target_include_directories(pva_labview PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}"
  "./src"
  "${EPICS_BASE_INCLUDE_DIRS}"
  "${PVXS_INCLUDE_DIRS}"
)
if(MSVC)
  target_include_directories(pva_labview PRIVATE
    "${EPICS_BASE_INCLUDE_DIRS}/compiler/msvc"
    "${EPICS_BASE_INCLUDE_DIRS}/os/win32"
  )
else()
  target_include_directories(pva_labview PRIVATE
    "${EPICS_BASE_INCLUDE_DIRS}/compiler/gcc"
    "${EPICS_BASE_INCLUDE_DIRS}/os/Linux"
  )
endif()

# Linker
if(MSVC)
  target_link_libraries(pva_labview PRIVATE
    "${LABVIEW_LIB}/labview.lib"
    "${EPICS_LIB}/Com.lib"
    "${EVENT_LIB}/event_core.lib"
    "${PVXS_LIB}/pvxs.lib"
  )
  # Module labview.lib is not compatible with the safe exception handling feature
  target_link_options(pva_labview PRIVATE "/SAFESEH:NO")
else()
  target_link_libraries(pva_labview PRIVATE
    "${PVXS_LIB}/libpvxs.so"
    "${EPICS_LIB}/libCom.so"
    "${EVENT_LIB}/libevent_core.so"
  )
endif()

GENERATE_EXPORT_HEADER(pva_labview)
