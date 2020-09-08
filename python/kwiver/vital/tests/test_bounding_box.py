"""
ckwg +31
Copyright 2020 by Kitware, Inc.
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

==============================================================================

Tests for BoundingBox python class, templates implemented as BoundingBoxD/F/I depending on type.

"""
import unittest
import nose.tools as nt
import numpy as np

from kwiver.vital.types import (
    BoundingBoxD as bboxD,
    BoundingBoxF as bboxF,
    BoundingBoxI as bboxI,
)


class TestBoundingBox(unittest.TestCase):
    @classmethod
    def setUp(self):
        self.ul_i = np.array([2, 1])
        self.ul_d = np.array([2.1, 1.3])
        self.lr_i = np.array([9, 11])
        self.width_i = 180
        self.height_i = 240
        self.width_d = 180.0
        self.height_i = 240.0
    def run_tests(self, bbox):
        pass
    def check_points(self, bbox):
        pass
    def check_dimensions(self, bbox):
        pass
    def check_has_points(self, bbox):
        pass
    def check_py_overloads(self, bbox):
        pass
    def test_constructorI(self):
        pass
    def test_bounding_boxes(self):
        pass