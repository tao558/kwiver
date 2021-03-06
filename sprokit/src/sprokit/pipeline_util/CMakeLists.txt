###
#
project(sprokit_pipeline_util)

set(pipeline_util_srcs
  bakery_base.cxx
  bakery_display.cxx
  cluster_bakery.cxx
  cluster_creator.cxx
  cluster_info.cxx
  cluster_splitter.cxx
  export_dot.cxx
  export_dot_exception.cxx
  export_pipe.cxx
  lex_processor.cxx
  load_pipe_exception.cxx
  loaded_cluster.cxx
  pipe_bakery.cxx
  pipe_bakery_exception.cxx
  pipe_display.cxx
  pipe_parser.cxx
  pipeline_builder.cxx
  provided_by_cluster.cxx
  token.cxx
  )

set(pipeline_util_headers
  export_dot.h
  export_dot_exception.h
  export_pipe.h
  literal_pipeline.h
  load_pipe_exception.h
  path.h
  pipe_bakery.h
  pipe_bakery_exception.h
  pipe_declaration_types.h
  )

set(pipeline_util_private_headers
  bakery_base.h
  bakery_display.h
  cluster_bakery.h
  cluster_creator.h
  cluster_info.h
  cluster_splitter.h
  lex_processor.h
  loaded_cluster.h
  pipe_display.h
  pipe_parser.h
  pipeline_builder.h
  provided_by_cluster.h
  token.h
  )

if (WIN32)
  set(path_sep "//073")
else ()
  set(path_sep "//072")
endif ()

set(sprokit_default_pipe_include_paths   "${CMAKE_INSTALL_PREFIX}/share/sprokit/pipelines/include")

if (KWIVER_USE_BUILD_TREE)
  set(sprokit_default_pipe_include_paths
    "${sprokit_default_pipe_include_paths}${path_sep}${KWIVER_SOURCE_DIR}/config/pipelines")
endif ()

set(SPROKIT_DEFAULT_PIPE_INCLUDE_PATHS "${sprokit_default_pipe_include_paths}"
  CACHE STRING "The default paths to search for pipe includes in")

set(sprokit_pipe_include_options  "DEFAULT_PIPE_INCLUDE_PATHS=\"${SPROKIT_DEFAULT_PIPE_INCLUDE_PATHS}\"")

set(load_pipe_build_options)

# It is not clear why windows is treated differently here
# Maybe the build options do not work the same.
if (WIN32)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include-paths.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include-paths.h")

  list(APPEND pipeline_util_private_headers
    include-paths.h.in)
else ()
  list(APPEND load_pipe_build_options
    ${sprokit_pipe_include_options})
endif ()

set_source_files_properties(pipeline_builder.cxx
  PROPERTIES
    COMPILE_DEFINITIONS "${load_pipe_build_options}")

kwiver_private_header_group(${pipeline_util_private_headers})

kwiver_add_library(sprokit_pipeline_util
  ${pipeline_util_srcs}
  ${pipeline_util_headers}
  ${pipeline_util_private_headers}
  )

target_link_libraries(sprokit_pipeline_util
  PUBLIC      sprokit_pipeline
            ${Boost_SYSTEM_LIBRARY}
  PRIVATE     vital_config
              vital_util
              vital_exceptions
            ${Boost_CHRONO_LIBRARY}
            ${Boost_THREAD_LIBRARY}
            ${CMAKE_THREAD_LIBS_INIT}
             kwiversys
 )

kwiver_install_headers(
  ${pipeline_util_headers}
  SUBDIR sprokit/pipeline_util
  )

# install export header
kwiver_install_headers(
  ${CMAKE_CURRENT_BINARY_DIR}/sprokit_pipeline_util_export.h
  SUBDIR   sprokit/pipeline_util
  NOPATH
  )
