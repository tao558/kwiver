# ckwg +29
# Copyright 2019 by Kitware, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  * Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
#  * Neither name of Kitware, Inc. nor the names of any contributors may be used
#    to endorse or promote products derived from this software without specific
#    prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
from __future__ import print_function

from kwiver.vital.algo import ImageObjectDetector
from kwiver.vital.types import DetectedObjectSet
from kwiver.vital.tests.helpers import CommonConfigurationMixin

class SimpleImageObjectDetector(CommonConfigurationMixin, ImageObjectDetector):
    """
    Implementation of ImageObjectDetector to test it

    Examples:
        >>> from kwiver.vital.modules import modules
        >>> modules.load_known_modules()
        >>> from kwiver.vital.algo import ImageObjectDetector
        >>> image_detector = ImageObjectDetector.create("SimpleImageObjectDetector")
        >>> from kwiver.vital.types import Image, ImageContainer
        >>> image = ImageContainer(Image())
        >>> detections = image_detector.detect(image)
        >>> print(len(detections)
        0

        With configuration that changes the threshold

        >>> modules.load_known_modules()
        >>> from kwiver.vital.algo import ImageObjectDetector
        >>> image_detector = ImageObjectDetector.create("SimpleImageObjectDetector")
        >>> from kwiver.vital.types import Image, ImageContainer
        >>> image = ImageContainer(Image())
        >>> from kwiver.vital.config import config
        >>> tc = config.empty_config()
        >>> tc.set_value("threshold", "0.5")
        >>> image_detector.check_configuration(tc)
        False
        >>> image_detector.set_configuration(tc)
        >>> image_detector.check_configuration(tc)
        True
    """
    def __init__(self):
        super(SimpleImageObjectDetector, self).__init__()

    def detect(self, image_data):
        dot = DetectedObjectSet()
        return dot

def __vital_algorithm_register__():
    from kwiver.vital.algo import algorithm_factory
    # Register Algorithm
    implementation_name  = "SimpleImageObjectDetector"
    if algorithm_factory.has_algorithm_impl_name(
                                SimpleImageObjectDetector.static_type_name(),
                                implementation_name):
        return
    algorithm_factory.add_algorithm( implementation_name,
                                "Test kwiver.vital.algo.ImageObjectDetector",
                                 SimpleImageObjectDetector )
    algorithm_factory.mark_algorithm_as_loaded( implementation_name )
