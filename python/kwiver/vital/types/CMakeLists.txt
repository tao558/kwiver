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


find_package(AutoPyBind11)

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

autopybind11_add_module(bounding_box_mod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/bounding_box_input.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/bb_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
get_target_property(bbox_srcs bounding_box_mod_files SOURCES)

kwiver_add_python_library(bounding_box
  vital/types
  ${bbox_srcs})
target_link_libraries(python-vital.types-bounding_box
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

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

kwiver_add_python_library(camera_intrinsics
  vital/types
  camera_intrinsics.cxx)
target_link_libraries(python-vital.types-camera_intrinsics
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(camera_map
  vital/types
  camera_map.cxx)
target_link_libraries(python-vital.types-camera_map
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

set_target_properties(python-vital.types-camera_mod PROPERTIES "_indexes" ${CMAKE_CURRENT_BINARY_DIR}/camera_mod.mdx)
file(GENERATE OUTPUT "python-vital-types-camera" CONTENT $<TARGET_PROPERTY:python-vital.types-camera_mod,SOURCES>)

autopybind11_add_module(camera_perspective
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrapper_inputs/camera_perspective_input.yml
                        CONFIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/configs/camera_perspective_config.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES vital python-vital.types-camera_mod
                        GEN_ONLY TRUE
                        INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
get_target_property(cam_perspective_srcs camera_perspective_files SOURCES)

kwiver_add_python_library(camera_perspective
  vital/types
  ${cam_perspective_srcs})
target_link_libraries(python-vital.types-camera_perspective
  PUBLIC ${PYTHON_LIBRARIES}
         vital
         )
add_dependencies(python-vital.types-camera_perspective python-vital.types-camera_mod)

kwiver_add_python_library(camera_perspective_map
  vital/types
  camera_perspective_map.cxx)
target_link_libraries(python-vital.types-camera_perspective_map
  PUBLIC ${PYTHON_LIBRARIES}
          vital)

kwiver_add_python_library(camera_rpc
  vital/types
  camera_rpc.cxx)
target_link_libraries(python-vital.types-camera_rpc
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(category_hierarchy
  vital/types
  category_hierarchy.cxx)
target_link_libraries(python-vital.types-category_hierarchy
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(class_map
  vital/types
  class_map.cxx)
target_link_libraries(python-vital.types-class_map
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

kwiver_add_python_library(database_query
  vital/types
  database_query.cxx)
target_link_libraries(python-vital.types-database_query
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

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

kwiver_add_python_library(detected_object
  vital/types
  detected_object.cxx)
target_link_libraries(python-vital.types-detected_object
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(detected_object_set
  vital/types
  detected_object_set.cxx)
target_link_libraries(python-vital.types-detected_object_set
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(feature
  vital/types
  feature.cxx)
target_link_libraries(python-vital.types-feature
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(feature_set
  vital/types
  feature_set.cxx)
target_link_libraries(python-vital.types-feature_set
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(feature_track_set
  vital/types
  feature_track_set.cxx)
target_link_libraries(python-vital.types-feature_track_set
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(fundamental_matrix
  vital/types
  fundamental_matrix.cxx)
target_link_libraries(python-vital.types-fundamental_matrix
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(geodesy
  vital/types
  geodesy.cxx)
target_link_libraries(python-vital.types-geodesy
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(geo_MGRS
  vital/types
  geo_MGRS.cxx)
target_link_libraries(python-vital.types-geo_MGRS
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(geo_covariance
  vital/types
  geo_covariance.cxx)
target_link_libraries(python-vital.types-geo_covariance
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(geo_point
  vital/types
  geo_point.cxx)
target_link_libraries(python-vital.types-geo_point
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(geo_polygon
  vital/types
  geo_polygon.cxx)
target_link_libraries(python-vital.types-geo_polygon
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(homography
  vital/types
  homography.cxx)
target_link_libraries(python-vital.types-homography
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(homography_f2f
  vital/types
  homography_f2f.cxx)
target_link_libraries(python-vital.types-homography_f2f
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(homography_f2w
  vital/types
  homography_f2w.cxx)
target_link_libraries(python-vital.types-homography_f2w
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

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

kwiver_add_python_library(polygon
  vital/types
  polygon.cxx)
target_link_libraries(python-vital.types-polygon
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(query_result
  vital/types
  query_result.cxx)
target_link_libraries(python-vital.types-query_result
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(rotation
  vital/types
  rotation.cxx)
target_link_libraries(python-vital.types-rotation
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(similarity
  vital/types
  similarity.cxx)
target_link_libraries(python-vital.types-similarity
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(sfm_constraints
  vital/types
  sfm_constraints.cxx)
target_link_libraries(python-vital.types-sfm_constraints
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(timestamp
  vital/types
  timestamp.cxx)
target_link_libraries(python-vital.types-timestamp
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(track
  vital/types
  track.cxx)
target_link_libraries(python-vital.types-track
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(track_descriptor
  vital/types
  track_descriptor.cxx)
target_link_libraries(python-vital.types-track_descriptor
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(track_interval
  vital/types
  track_interval.cxx)
target_link_libraries(python-vital.types-track_interval
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(track_set
  vital/types
  track_set.cxx)
target_link_libraries(python-vital.types-track_set
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(transform_2d
  vital/types
  transform_2d.cxx)
target_link_libraries(python-vital.types-transform_2d
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(uid
  vital/types
  uid.cxx)
target_link_libraries(python-vital.types-uid
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

kwiver_add_python_library(object_track_set
  vital/types
  object_track_set.cxx)
target_link_libraries(python-vital.types-object_track_set
  PUBLIC ${PYTHON_LIBRARIES}
         vital)

if(NOT SKBUILD)
  kwiver_create_python_init(vital/types
    types
    bounding_box
    category_hierarchy
    camera
    camera_intrinsics
    camera_map
    camera_perspective
    camera_perspective_map
    camera_rpc
    class_map
    color
    covariance_mod
    database_query
    descriptor
    descriptor_request
    descriptor_set
    detected_object
    detected_object_set
    feature
    feature_set
    feature_track_set
    fundamental_matrix
    geodesy
    geo_covariance
    geo_MGRS
    geo_polygon
    geo_point
    transform_2d
    homography
    homography_f2f
    homography_f2w
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
    track
    track_descriptor
    track_interval
    track_set
    uid
    object_track_set
    activity_mod
  )
endif()
