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

from kwiver.vital.modules import modules
from kwiver.vital.algo import ComputeAssociationMatrix

from unittest.mock import Mock

class TestVitalComputeAssociationMatrix(object):
    def setUp(self):
        modules.load_known_modules()
        self.algorithm = ComputeAssociationMatrix.create("SimpleComputeAssociationMatrix")

    # Test compute function with an instance of example_algorithm
    @nose.tools.raises(TypeError)
    def test_empty_compute(self):
        self.algorithm.compute()

    # Test compute with all the attributes
    def test_compute(self):
        timestamp = Mock()
        image = Mock()
        tracks = Mock()
        detections = Mock()
        matrix = Mock()
        considered = Mock()
        nose.tools.ok_(self.algorithm.compute(timestamp, image,
                                                     tracks, detections,
                                                     matrix, considered))
        timestamp.method.assert_called_once_with()
        image.method.assert_called_once_with()
        tracks.method.assert_called_once_with()
        detections.method.assert_called_once_with()
        matrix.method.assert_called_once_with()
        considered.method.assert_called_once_with()
