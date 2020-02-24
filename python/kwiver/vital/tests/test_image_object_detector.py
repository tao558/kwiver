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

Tests for image object detector interface class
"""
from __future__ import print_function, absolute_import

import nose.tools

from kwiver.vital.algo import ImageObjectDetector
from kwiver.vital.types import Image
from kwiver.vital.types import ImageContainer
from kwiver.vital.types import DetectedObjectSet
from kwiver.vital.modules import modules
from kwiver.vital.tests.helpers import generate_dummy_config
from kwiver.vital.config import config


def _dummy_detector_cfg():
    return generate_dummy_config(threshold=0.4)


class TestVitalImageObjectDetector(object):
    # Test detect function with an instance of example_detector
    # When an image container is not passed it raises TypeError
    @nose.tools.raises(TypeError)
    def test_empty_detect(self):
        modules.load_known_modules()
        detector = ImageObjectDetector.create("SimpleImageObjectDetector")
        detector.detect()

    # For an image container it returns a detected object set of size 1
    def test_detect(self):
        modules.load_known_modules()
        detector = ImageObjectDetector.create("SimpleImageObjectDetector")
        image = Image()
        image_container = ImageContainer(image)
        detections = detector.detect(image_container)
        nose.tools.ok_(detections is not None, "Unexpected empty detections")
        nose.tools.assert_equal(len(detections), 0)
