project(vital_python_types)

include_directories(${pybind11_INCLUDE_DIR})

set( vital_python_headers
     image.h
     image_container.h
  )

set( vital_python_sources
     image.cxx
     image_container.cxx
     types_module.cxx
   )

kwiver_add_python_library(types
  vital/types
  ${vital_python_headers}
  ${vital_python_sources}
  )

target_link_libraries(python-vital.types-types
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/activity_mod)
autopybind11_add_module(activity_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/activity_wrapper_input.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/activity_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
get_target_property(activity_mod_srcs activity_mod_files SOURCES)

kwiver_add_python_library(activity_mod
  vital/types
  ${activity_mod_srcs}
  )

target_link_libraries(python-vital.types-activity_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bb_mod)

autopybind11_add_module(bounding_box_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/bounding_box_input.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/bb_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
get_target_property(bbox_srcs bounding_box_mod_files SOURCES)

kwiver_add_python_library(bounding_box_mod
  vital/types
  ${bbox_srcs})
target_link_libraries(python-vital.types-bounding_box_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cam_mod)
autopybind11_add_module(camera_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/camera_input.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/camera_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
get_target_property(camera_srcs camera_mod_files SOURCES)
kwiver_add_python_library(camera_mod
  vital/types
  ${camera_srcs})
target_link_libraries(python-vital.types-camera_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(camera_intrinsics
#   vital/types
#   camera_intrinsics.cxx)
# target_link_libraries(python-vital.types-camera_intrinsics
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(camera_map
#   vital/types
#   camera_map.cxx)
# target_link_libraries(python-vital.types-camera_map
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# autopybind11_add_module(camera_perspective
#                         YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/camera_perspective_input.yml
#                         CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/camera_perspective_config.yml
#                         DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#                         LINK_LIBRARIES vital python-vital.types-camera_mod
#                         GEN_ONLY TRUE
#                         INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
# get_target_property(cam_perspective_srcs camera_perspective_files SOURCES)

# kwiver_add_python_library(camera_perspective
#   vital/types
#   ${cam_perspective_srcs})
# target_link_libraries(python-vital.types-camera_perspective
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital
#          )
# add_dependencies(python-vital.types-camera_perspective python-vital.types-camera_mod)

# kwiver_add_python_library(camera_perspective_map
#   vital/types
#   camera_perspective_map.cxx)
# target_link_libraries(python-vital.types-camera_perspective_map
#   PUBLIC ${PYTHON_LIBRARIES}
#           vital)

# kwiver_add_python_library(camera_rpc
#   vital/types
#   camera_rpc.cxx)
# target_link_libraries(python-vital.types-camera_rpc
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

autopybind11_add_module(category_hierarchy_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/category_hierarchy.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/category_hierarchy_conf.yml
                        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(category_hierarchy_mod_srcs category_hierarchy_mod_files SOURCES)

kwiver_add_python_library(category_hierarchy_mod
  vital/types
  ${category_hierarchy_mod_srcs})
target_link_libraries(python-vital.types-category_hierarchy_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(class_map_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}wrapper_inputs/class_map_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/class_map_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(class_map_mod_srcs class_map_mod_files SOURCES)

kwiver_add_python_library(class_map_mod
  vital/types
  ${class_map_mod_srcs})
target_link_libraries(python-vital.types-class_map_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(color
#   vital/types
#   color.cxx)
# target_link_libraries(python-vital.types-color
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

autopybind11_add_module(color
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/color_wrapper_input.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/color_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(color_srcs color_files SOURCES)

kwiver_add_python_library(color
  vital/types
  ${color_srcs})
target_link_libraries(python-vital.types-color
  PUBLIC ${PYTHON_LIBRARIES}
         vital)


autopybind11_add_module(covariance_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/covariance_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/covar_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
get_target_property(covar_mod_srcs covariance_mod_files SOURCES)


kwiver_add_python_library(covariance_mod
  vital/types
  ${covar_mod_srcs})
target_link_libraries(python-vital.types-covariance_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(database_query_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/database_query_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/database_query_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(database_query_mod_srcs database_query_mod_files SOURCES)

kwiver_add_python_library(database_query_mod
  vital/types
  ${database_query_mod_srcs})
target_link_libraries(python-vital.types-database_query_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# autopybind11_add_module(descriptor_mod
#                         YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/descriptors_wrapper.yml
#                         CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/descriptors_conf.yml
#                         DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#                         LINK_LIBRARIES vital
#                         GEN_ONLY TRUE
#                         INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})


# get_target_property(descriptor_mod_srcs descriptor_mod_files SOURCES)


kwiver_add_python_library(descriptor
  vital/types
  descriptor.cxx)
target_link_libraries(python-vital.types-descriptor
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(descriptor_request
  vital/types
  descriptor_request.cxx)
target_link_libraries(python-vital.types-descriptor_request
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(descriptor_set
  vital/types
  descriptor_set.cxx)
target_link_libraries(python-vital.types-descriptor_set
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(detected_object_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/detected_object_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/detected_object_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(detected_object_mod_srcs detected_object_mod_files SOURCES)

kwiver_add_python_library(detected_object_mod
  vital/types
  ${detected_object_mod_srcs})
target_link_libraries(python-vital.types-detected_object_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(detected_object_set
#   vital/types
#   detected_object_set.cxx)
# target_link_libraries(python-vital.types-detected_object_set
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

autopybind11_add_module(feature_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/feature_mod_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/feature_mod_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(feature_mod_srcs feature_mod_files SOURCES)

kwiver_add_python_library(feature_mod
  vital/types
  ${feature_mod_srcs})
target_link_libraries(python-vital.types-feature_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(feature_set
#   vital/types
#   feature_set.cxx)
# target_link_libraries(python-vital.types-feature_set
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(feature_track_set
#   vital/types
#   feature_track_set.cxx)
# target_link_libraries(python-vital.types-feature_track_set
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

autopybind11_add_module(fundamental_matrix_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/fundamental_matrix_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/fundamental_matrix_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(fundamental_matrix_srcs fundamental_matrix_mod_files SOURCES)


kwiver_add_python_library(fundamental_matrix_mod
  vital/types
  ${fundamental_matrix_srcs})
target_link_libraries(python-vital.types-fundamental_matrix_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(geo_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/geo_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/geo_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(geo_mod_srcs geo_mod_files SOURCES)

kwiver_add_python_library(geo_mod
  vital/types
  ${geo_mod_srcs})
target_link_libraries(python-vital.types-geo_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(geodesy
#   vital/types
#   geodesy.cxx)
# target_link_libraries(python-vital.types-geodesy
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(geo_MGRS
#   vital/types
#   geo_MGRS.cxx)
# target_link_libraries(python-vital.types-geo_MGRS
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(geo_covariance
#   vital/types
#   geo_covariance.cxx)
# target_link_libraries(python-vital.types-geo_covariance
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(geo_point
#   vital/types
#   geo_point.cxx)
# target_link_libraries(python-vital.types-geo_point
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(geo_polygon
#   vital/types
#   geo_polygon.cxx)
# target_link_libraries(python-vital.types-geo_polygon
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

autopybind11_add_module(homography_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/homography_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/homography_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(homography_mod_srcs homography_mod_files SOURCES)

kwiver_add_python_library(homography_mod
  vital/types
  ${homography_mod_srcs})
target_link_libraries(python-vital.types-homography_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(homography_f2f
#   vital/types
#   homography_f2f.cxx)
# target_link_libraries(python-vital.types-homography_f2f
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(homography_f2w
#   vital/types
#   homography_f2w.cxx)
# target_link_libraries(python-vital.types-homography_f2w
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

kwiver_add_python_library(iqr_feedback
  vital/types
  iqr_feedback.cxx)
target_link_libraries(python-vital.types-iqr_feedback
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(landmark
#   vital/types
#   landmark.cxx)
# target_link_libraries(python-vital.types-landmark
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(landmark_map
#   vital/types
#   landmark_map.cxx)
# target_link_libraries(python-vital.types-landmark_map
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

kwiver_add_python_library(local_cartesian
  vital/types
  local_cartesian.cxx)
target_link_libraries(python-vital.types-local_cartesian
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(local_geo_cs
  vital/types
  local_geo_cs.cxx)
target_link_libraries(python-vital.types-local_geo_cs
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(match_set
  vital/types
  match_set.cxx)
target_link_libraries(python-vital.types-match_set
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(metadata
  vital/types
  metadata.cxx)
target_link_libraries(python-vital.types-metadata
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(metadata_map
  vital/types
  metadata_map.cxx)
target_link_libraries(python-vital.types-metadata_map
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(metadata_tags
  vital/types
  metadata_tags.cxx)
target_link_libraries(python-vital.types-metadata_tags
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(metadata_traits
  vital/types
  metadata_traits.cxx)
target_link_libraries(python-vital.types-metadata_traits
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/point_mod)

autopybind11_add_module(point_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/point_wrapper_input.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/point_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR} )

get_target_property(point_mod_srcs point_mod_files SOURCES)
kwiver_add_python_library(point_mod
  vital/types
  ${point_mod_srcs})
target_link_libraries(python-vital.types-point_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(polygon_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/polygon_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/polygon_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR} )

get_target_property(polygon_mod_srcs polygon_mod_files SOURCES)

kwiver_add_python_library(polygon_mod
  vital/types
  ${polygon_mod_srcs})
target_link_libraries(python-vital.types-polygon_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(query_result_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/query_reseult_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/query_result_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR} )

get_target_property(query_result_mod_srcs query_result_mod_files SOURCES)

kwiver_add_python_library(query_result_mod
  vital/types
  ${query_result_mod_srcs})
target_link_libraries(python-vital.types-query_result_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(rotation_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/rotation_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/rotation_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(rotation_mod_srcs rotation_mod_files SOURCES)

kwiver_add_python_library(rotation_mod
  vital/types
  ${rotation_mod_srcs})
target_link_libraries(python-vital.types-rotation_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(similarity_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/similarity_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/similarity_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(similarity_mod_srcs similarity_mod_files SOURCES)

kwiver_add_python_library(similarity_mod
  vital/types
  ${similarity_mod_srcs})
target_link_libraries(python-vital.types-similarity_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(sfm_constraints_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/sfm_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/sfm_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(sfm_constraints_mod_srcs sfm_constraints_mod_files SOURCES)

kwiver_add_python_library(sfm_constraints_mod
  vital/types
  ${sfm_constraints_mod_srcs})
target_link_libraries(python-vital.types-sfm_constraints_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(timestamp_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/timestamp_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/timestamp_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(timestamp_mod_srcs timestamp_mod_files SOURCES)

kwiver_add_python_library(timestamp_mod
  vital/types
  ${timestamp_mod_srcs})
target_link_libraries(python-vital.types-timestamp_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(track_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/track_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/track_mod_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

get_target_property(track_mod_srcs track_mod_files SOURCES)

kwiver_add_python_library(track
  vital/types
  ${track_mod_srcs})

target_link_libraries(python-vital.types-track
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

# kwiver_add_python_library(track_descriptor
#   vital/types
#   track_descriptor.cxx)
# target_link_libraries(python-vital.types-track_descriptor
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(track_interval
#   vital/types
#   track_interval.cxx)
# target_link_libraries(python-vital.types-track_interval
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

# kwiver_add_python_library(track_set
#   vital/types
#   track_set.cxx)
# target_link_libraries(python-vital.types-track_set
#   PUBLIC ${PYTHON_LIBRARIES}
#          vital)

autopybind11_add_module(transform_2d_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/transform_2d_wrapper.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/transform_2d_conf.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR} )

get_target_property(transform_2d_mod_srcs transform_2d_mod_files SOURCES)

kwiver_add_python_library(transform_2d_mod
  vital/types
  ${transform_2d_mod_srcs})
target_link_libraries(python-vital.types-transform_2d_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(uid_mod
         YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/uid_wrapper.yml
         CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/uid_conf.yml
         DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
         LINK_LIBRARIES vital
         GEN_ONLY TRUE
         INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR} )

get_target_property(uid_mod_srcs uid_mod_files SOURCES)

kwiver_add_python_library(uid_mod
  vital/types
  ${uid_mod_srcs})
target_link_libraries(python-vital.types-uid_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

autopybind11_add_module(object_track_set_mod
         YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/object_track_set_wrapper.yml
         CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/object_track_set_conf.yml
         DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
         LINK_LIBRARIES vital
         GEN_ONLY TRUE
         INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR} )

get_target_property(object_track_set_mod_srcs object_track_set_mod_files SOURCES)

kwiver_add_python_library(object_track_set_mod
  vital/types
  ${object_track_set_mod_srcs})
target_link_libraries(python-vital.types-object_track_set_mod
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

if(NOT SKBUILD)
  kwiver_create_python_init(vital/types
    types
    bounding_box_mod
    category_hierarchy
    camera_mod
    class_map
    color
    covariance_mod
    database_query_mod
    descriptor_mod
    # descriptor_request
    # descriptor_set
    # detected_object
    detected_object_set
    feature_mod
    # feature_set
    # feature_track_set
    fundamental_matrix_mod
    geo_mod
    # geodesy
    # geo_covariance
    # geo_MGRS
    # geo_polygon
    # geo_point
    transform_2d
    homography_mod
    # homography_f2f
    # homography_f2w
    iqr_feedback
    # landmark
    # landmark_map
    local_cartesian
    rotation
    local_geo_cs
    match_set
    metadata
    metadata_map
    metadata_tags
    metadata_traits
    point_mod
    polygon
    query_result
    similarity
    sfm_constraints
    timestamp
    track_mod
    # track_descriptor
    # track_interval
    # track_set
    uid
    object_track_set
    activity_mod
  )
endif()
