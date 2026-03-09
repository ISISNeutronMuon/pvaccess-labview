add_library(labview STATIC IMPORTED)
if(WIN32)
  set_target_properties(labview PROPERTIES IMPORTED_LOCATION "$ENV{LABVIEW_LIB}/labview.lib")
endif()
