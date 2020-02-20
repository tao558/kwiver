"""
ckwg +29
Copyright 2019 by Kitware, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither name of Kitware, Inc. nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific
   prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Tests for associate detection to tracks interface class
"""
from __future__ import print_function, absolute_import

import nose.tools

from kwiver.vital.algo import AssociateDetectionsToTracks
from kwiver.vital.types import Timestamp, Image, ImageContainer
from kwiver.vital.types import ObjectTrackSet
from kwiver.vital.types import DetectedObjectSet
from kwiver.vital.modules import modules
import numpy as np

from kwiver.vital.tests.helpers import generate_dummy_config
from kwiver.vital.config import config

def _dummy_algorithm_cfg():
    return generate_dummy_config(threshold=0.3)

class TestVitalAssociateDetectionsToTracks(object):
    # Test associate function with an instance of example_algorithm
    @nose.tools.raises(TypeError)
    def test_empty_associate(self):
        modules.load_known_modules()
        algorithm = AssociateDetectionsToTracks.create(
                                    "SimpleAssociateDetectionsToTracks")
        algorithm.associate()

    # For valid associate, the algorithm return true
    def test_detect(self):
        modules.load_known_modules()
        algorithm = AssociateDetectionsToTracks.create(
                                    "SimpleAssociateDetectionsToTracks")

        image = ImageContainer(Image())
        timestamp = Timestamp(0,0)
        tracks = ObjectTrackSet()
        detections = DetectedObjectSet()
        cost_matrix = np.zeros([3,3])
        op_tracks = ObjectTrackSet()
        unused_detections = DetectedObjectSet()
        nose.tools.ok_(algorithm.associate(timestamp, image, tracks, detections,
                                           cost_matrix, op_tracks,
                                           unused_detections),
                       "Unexpected empty detections")
