/*ckwg +29
 * Copyright 2020 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "track_features.h"

#include <vital/algo/image_io.h>
#include <vital/algo/convert_image.h>
#include <vital/algo/track_features.h>
#include <vital/algo/compute_ref_homography.h>
#include <vital/algo/video_input.h>
#include <vital/io/track_set_io.h>
#include <vital/plugin_loader/plugin_manager.h>
#include <vital/config/config_block_io.h>
#include <vital/config/config_block.h>
#include <vital/config/config_parser.h>
#include <vital/util/get_paths.h>
#include <vital/util/transform_image.h>

#include <kwiversys/SystemTools.hxx>
#include <kwiversys/CommandLineArguments.hxx>

#include <arrows/core/colorize.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace kwiver {
namespace arrows {
namespace mvg {


namespace {

typedef kwiversys::SystemTools ST;
typedef kwiversys::CommandLineArguments argT;

kwiver::vital::logger_handle_t main_logger( kwiver::vital::get_logger( "track_features_tool" ) );

// ------------------------------------------------------------------
kwiver::vital::config_block_sptr default_config()
{
  kwiver::vital::config_block_sptr config = kwiver::vital::config_block::empty_config("feature_tracker_tool");

  config->set_value("video_source", "",
                    "Path to an input file to be opened as a video. "
                    "This could be either a video file or a text file "
                    "containing new-line separated paths to sequential "
                    "image files.");
  config->set_value("mask_list_file", "",
                    "Optional path to an input file containing new-line "
                    "separated paths to mask images. This list should be "
                    "parallel in association to frames provided by the "
                    "``video_source`` video. Mask images must be the same size "
                    "as the image they are associated with.\n"
                    "\n"
                    "Leave this blank if no image masking is desired.");
  config->set_value("invert_masks", false,
                    "If true, all mask images will be inverted after loading. "
                    "This is useful if mask images read in use positive "
                    "values to indicated masked areas instead of non-masked "
                    "areas.");
  config->set_value("expect_multichannel_masks", false,
                    "A majority of the time, mask images are a single channel, "
                    "however it is feasibly possible that certain "
                    "implementations may use multi-channel masks. If this is "
                    "true we will expect multiple-channel mask images, "
                    "warning when a single-channel mask is provided. If this "
                    "is false we error upon seeing a multi-channel mask "
                    "image.");
  config->set_value("output_tracks_file", "",
                    "Path to a file to write output tracks to. If this "
                    "file exists, it will be overwritten.");
  config->set_value("output_homography_file", "",
                    "Optional path to a file to write source-to-reference "
                    "homographies for each frame. Leave blank to disable this "
                    "output. The output_homography_generator algorithm type "
                    "only needs to be set if this is set.");

  kwiver::vital::algo::video_input::get_nested_algo_configuration("video_reader", config,
                                      kwiver::vital::algo::video_input_sptr());
  kwiver::vital::algo::track_features::get_nested_algo_configuration("feature_tracker", config,
                                      kwiver::vital::algo::track_features_sptr());
  kwiver::vital::algo::image_io::get_nested_algo_configuration("image_reader", config,
                                      kwiver::vital::algo::image_io_sptr());
  kwiver::vital::algo::convert_image::get_nested_algo_configuration("convert_image", config,
                                      kwiver::vital::algo::convert_image_sptr());
  kwiver::vital::algo::compute_ref_homography::get_nested_algo_configuration("output_homography_generator",
                              config, kwiver::vital::algo::compute_ref_homography_sptr());
  return config;
}


// ------------------------------------------------------------------
bool check_config(kwiver::vital::config_block_sptr config)
{
  bool config_valid = true;

#define KWIVER_CONFIG_FAIL(msg) \
  LOG_ERROR(main_logger, "Config Check Fail: " << msg); \
  config_valid = false

  // A given homography file is invalid if it names a directory, or if its
  // parent path either doesn't exist or names a regular file.
  if ( config->has_value("output_homography_file")
    && config->get_value<std::string>("output_homography_file") != "" )
  {
    kwiver::vital::config_path_t fp = config->get_value<kwiver::vital::config_path_t>("output_homography_file");
    if ( kwiversys::SystemTools::FileIsDirectory( fp ) )
    {
      KWIVER_CONFIG_FAIL("Given output homography file is a directory! "
                        << "(Given: " << fp << ")");
    }
    else if ( ST::GetFilenamePath( fp ) != "" &&
              ! ST::FileIsDirectory( ST::GetFilenamePath( fp ) ))
    {
      KWIVER_CONFIG_FAIL("Given output homography file does not have a valid "
                        << "parent path! (Given: " << fp << ")");
    }

    // Check that compute_ref_homography algo is correctly configured
    if( !kwiver::vital::algo::compute_ref_homography
             ::check_nested_algo_configuration("output_homography_generator",
                                               config) )
    {
      KWIVER_CONFIG_FAIL("output_homography_generator configuration check failed");
    }
  }

  if ( ! config->has_value("video_source") ||
      config->get_value<std::string>("video_source") == "")
  {
    KWIVER_CONFIG_FAIL("Config needs value video_source");
  }
  else
  {
    std::string path = config->get_value<std::string>("video_source");
    if ( ! ST::FileExists( kwiver::vital::path_t(path), true ) )
    {
      KWIVER_CONFIG_FAIL("video_source path, " << path << ", does not exist or is not a regular file");
    }
  }

  // If given an mask image list file, check that the file exists and is a file
  if (config->has_value("mask_list_file") && config->get_value<std::string>("mask_list_file") != "" )
  {
    std::string mask_list_file = config->get_value<std::string>("mask_list_file");
    if (mask_list_file != "" && ! ST::FileExists( kwiver::vital::path_t(mask_list_file), true ))
    {
      KWIVER_CONFIG_FAIL("mask_list_file path, " << mask_list_file << ", does not exist");
    }
  }

  if (!config->has_value("output_tracks_file") ||
      config->get_value<std::string>("output_tracks_file") == "" )
  {
    KWIVER_CONFIG_FAIL("Config needs value output_tracks_file");
  }
  else if ( ! ST::FileIsDirectory( ST::CollapseFullPath( ST::GetFilenamePath(
              config->get_value<kwiver::vital::path_t>("output_tracks_file") ) ) ) )
  {
    KWIVER_CONFIG_FAIL("output_tracks_file is not in a valid directory");
  }

  if (!kwiver::vital::algo::video_input::check_nested_algo_configuration("video_reader", config))
  {
    KWIVER_CONFIG_FAIL("video_reader configuration check failed");
  }

  if (!kwiver::vital::algo::track_features::check_nested_algo_configuration("feature_tracker", config))
  {
    KWIVER_CONFIG_FAIL("feature_tracker configuration check failed");
  }

  if (!kwiver::vital::algo::image_io::check_nested_algo_configuration("image_reader", config))
  {
    KWIVER_CONFIG_FAIL("image_reader configuration check failed");
  }

  if (!kwiver::vital::algo::convert_image::check_nested_algo_configuration("convert_image", config))
  {
    KWIVER_CONFIG_FAIL("convert_image configuration check failed");
  }

#undef KWIVER_CONFIG_FAIL

  return config_valid;
}
} // end namespace

// ----------------------------------------------------------------------------
int
track_features::
run()
{
  namespace kv = ::kwiver::vital;
  namespace kva = ::kwiver::vital::algo;

  try
  {
    auto& cmd_args = command_args();
    std::string opt_config;
    std::string opt_out_config;

    if ( cmd_args["help"].as<bool>() )
    {
      std::cout << m_cmd_options->help();
      return EXIT_SUCCESS;
    }
    if ( cmd_args.count("config") )
    {
      opt_config = cmd_args["config"].as<std::string>();
    }
    if ( cmd_args.count("output-config") > 0 )
    {
      opt_out_config = cmd_args["output-config"].as<std::string>();
    }

    // Set config to algo chain
    // Get config from algo chain after set
    // Check config validity, store result
    //
    // If -o/--output-config given, output config result and notify of current (in)validity
    // Else error if provided config not valid.

    // Set up top level configuration w/ defaults where applicable.
    kv::config_block_sptr config = default_config();
    kva::video_input_sptr video_reader;
    kva::track_features_sptr feature_tracker;
    kva::image_io_sptr image_reader;
    kva::convert_image_sptr image_converter;
    kva::compute_ref_homography_sptr out_homog_generator;

    // If -c/--config given, read in confg file, merge in with default just generated
    if( ! opt_config.empty() )
    {
      config->merge_config(kv::read_config_file(opt_config));
    }

    kva::video_input::set_nested_algo_configuration("video_reader", config, video_reader);
    kva::video_input::get_nested_algo_configuration("video_reader", config, video_reader);
    kva::track_features::set_nested_algo_configuration("feature_tracker", config, feature_tracker);
    kva::track_features::get_nested_algo_configuration("feature_tracker", config, feature_tracker);
    kva::image_io::set_nested_algo_configuration("image_reader", config, image_reader);
    kva::image_io::get_nested_algo_configuration("image_reader", config, image_reader);
    kva::convert_image::set_nested_algo_configuration("convert_image", config, image_converter);
    kva::convert_image::get_nested_algo_configuration("convert_image", config, image_converter);
    kva::compute_ref_homography::set_nested_algo_configuration("output_homography_generator", config, out_homog_generator);
    kva::compute_ref_homography::get_nested_algo_configuration("output_homography_generator", config, out_homog_generator);

    bool valid_config = check_config(config);

    if( ! opt_out_config.empty() )
    {
      write_config_file(config, opt_out_config );
      if(valid_config)
      {
        LOG_INFO(main_logger, "Configuration file contained valid parameters and may be used for running");
      }
      else
      {
        LOG_WARN(main_logger, "Configuration deemed not valid.");
      }
      return EXIT_SUCCESS;
    }
    else if(!valid_config)
    {
      LOG_ERROR(main_logger, "Configuration not valid.");
      return EXIT_FAILURE;
    }

    // Attempt opening input and output files.
    //  - filepath validity checked above
    auto const video_source = config->get_value<std::string>("video_source");
    auto const mask_list_file = config->get_value<std::string>("mask_list_file");
    auto const invert_masks = config->get_value<bool>("invert_masks");
    auto const expect_multichannel_masks = config->get_value<bool>("expect_multichannel_masks");
    auto const output_tracks_file = config->get_value<std::string>("output_tracks_file");


    LOG_INFO( main_logger, "Reading Video" );
    video_reader->open(video_source);

    // Pre-scan the video to get an accurate frame count
    // We may wish to remove this later if we start operating on live streams
    kv::timestamp ts;
    std::vector<kv::timestamp> timestamps;
    while( video_reader->next_frame(ts) )
    {
      timestamps.push_back(ts);
    }
    // close and re-open to return to the video start
    video_reader->close();
    video_reader->open(video_source);


    // Create mask image list if a list file was given, else fill list with empty
    // images. Files vector will only be populated if the use_masks bool is true
    bool use_masks = false;
    std::vector<kv::path_t> mask_files;
    if( mask_list_file != "" )
    {
      LOG_DEBUG( main_logger, "Checking paired mask images from list file" );

      use_masks = true;
      // Load file stream
      std::ifstream mask_ifs(mask_list_file.c_str());
      if( !mask_ifs )
      {
        VITAL_THROW( kv::path_not_exists, mask_list_file );
      }
      // load filepaths from file
      for( std::string line; std::getline(mask_ifs, line); )
      {
        mask_files.push_back(line);
        if( ! ST::FileExists( mask_files[mask_files.size()-1], true ) )
        {
          VITAL_THROW( kv::path_not_exists, mask_files[mask_files.size()-1] );
        }
      }
      // Check that image/mask list sizes are the same
      if( timestamps.size() != mask_files.size() )
      {
        VITAL_THROW( kv::invalid_value,
                     "video and mask file lists have "
                     "different frame counts");
      }
      LOG_DEBUG( main_logger,
                 "Validated " << mask_files.size() << " mask image files." );
    }

    // verify that we can open the output file for writing
    // so that we don't find a problem only after spending
    // hours of computation time.
    std::ofstream ofs(output_tracks_file.c_str());
    if (!ofs)
    {
      LOG_ERROR(main_logger, "Could not open track file for writing: \""
                << output_tracks_file << "\"");
      return EXIT_FAILURE;
    }
    ofs.close();

    // Create the output homography file stream if specified
    // Validity of file path checked during configuration file validity check.
    std::ofstream homog_ofs;
    if ( config->has_value("output_homography_file") &&
         config->get_value<std::string>("output_homography_file") != "" )
    {
      kv::path_t homog_fp = config->get_value<kv::path_t>("output_homography_file");
      homog_ofs.open( homog_fp.c_str() );
      if ( !homog_ofs )
      {
        LOG_ERROR(main_logger, "Could not open homography file for writing: "
                  << homog_fp);
        return EXIT_FAILURE;
      }
    }

    // Track features on each frame sequentially
    kv::feature_track_set_sptr tracks;
    while( video_reader->next_frame(ts) )
    {
      LOG_INFO(main_logger, "processing frame "<<ts.get_frame() );

      auto const image = video_reader->frame_image();
      auto const mdv = video_reader->frame_metadata();
      auto converted_image = image_converter->convert( image );
      if( !mdv.empty() )
      {
        converted_image->set_metadata( mdv[0] );
      }

      // Load the mask for this image if we were given a mask image list
      kv::image_container_sptr mask, converted_mask;
      if( use_masks )
      {
        mask = image_reader->load( mask_files[ts.get_frame()] );

        // error out if we are not expecting a multi-channel mask
        if( !expect_multichannel_masks && mask->depth() > 1 )
        {
          LOG_ERROR( main_logger,
                     "Encounted multi-channel mask image!" );
          return EXIT_FAILURE;
        }
        else if( expect_multichannel_masks && mask->depth() == 1 )
        {
          LOG_WARN( main_logger,
                    "Expecting multi-channel masks but received one that was "
                    "single-channel." );
        }

        if( invert_masks )
        {
          LOG_DEBUG( main_logger,
                     "Inverting mask image pixels" );
          kv::image_of<bool> mask_image;
          kv::cast_image( mask->get_image(), mask_image );
          kv::transform_image( mask_image, [] (bool b) { return !b; } );
          LOG_DEBUG( main_logger,
                     "Inverting mask image pixels -- Done" );
          mask = std::make_shared<kv::simple_image_container>( mask_image );
        }

        converted_mask = image_converter->convert( mask );
      }

      tracks = feature_tracker->track(tracks, ts.get_frame(),
                                      converted_image, converted_mask);
      if (tracks)
      {
        tracks = kwiver::arrows::core::extract_feature_colors(tracks, *image, ts.get_frame());
      }

      // Compute ref homography for current frame with current track set + write to file
      // -> still doesn't take into account a full shotbreak, which would incur a track reset
      if ( homog_ofs.is_open() )
      {
        LOG_DEBUG(main_logger, "writing homography");
        homog_ofs << *(out_homog_generator->estimate(ts.get_frame(), tracks)) << std::endl;
      }
    }

    if ( homog_ofs.is_open() )
    {
      homog_ofs.close();
    }

    // Writing out tracks to file
    kv::write_feature_track_file(tracks, output_tracks_file);

    return EXIT_SUCCESS;
  }
  catch (std::exception const& e)
  {
    LOG_ERROR(main_logger, "Exception caught: " << e.what());

    return EXIT_FAILURE;
  }
  catch (...)
  {
    LOG_ERROR(main_logger, "Unknown exception caught");

    return EXIT_FAILURE;
  }
} // run

// ----------------------------------------------------------------------------
void
track_features::
add_command_options()
{
  m_cmd_options->custom_help( wrap_text( "[options]\n" ) );

  m_cmd_options->add_options()
    ( "h,help",     "Display applet usage" )
    ( "c,config",   "Configuration file for tool", cxxopts::value<std::string>() )
    ( "o,output-config",
      "Output a configuration. This may be seeded with a "
      "configuration file from -c/--config.",
      cxxopts::value<std::string>() )
    ;
}

// ============================================================================
track_features::
track_features()
{ }

} } } // end namespace
