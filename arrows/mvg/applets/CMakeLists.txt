#
# CMake file for the arrows.mvg.applets
#

set( sources
  register_applets.cxx

  track_features.cxx
  )

set( headers
  track_features.h
  )

###
# Add our plugin path to the default list
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

###
# Add path to applets so plugin loader can find them
if(NOT SKBUILD)
  kwiver_make_module_path( ${KWIVER_BINARY_DIR} ${kwiver_plugin_applets_subdir} )
  kwiver_add_module_path( ${kwiver_module_path_result} )
endif()
# Add applet plugin
kwiver_add_plugin( kwiver_algo_mvg_applets
  SUBDIR       ${kwiver_plugin_applets_subdir}
  SOURCES      ${sources} ${headers}
  PRIVATE      kwiver_algo_core
               kwiver_algo_mvg
               kwiver_tools_applet
               kwiversys
)
