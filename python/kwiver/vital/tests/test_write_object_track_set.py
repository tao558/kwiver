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

Tests for write object track set interface class
"""
import nose.tools
import os

from kwiver.vital.algo import WriteObjectTrackSet
from kwiver.vital.modules import modules
from kwiver.vital.config import config
from unittest import TestCase
from kwiver.vital.tests.helpers import generate_dummy_config
from kwiver.vital.types import ObjectTrackSet
from test_basic import TestVitalAlgorithmBasic, _dummy_algorithm_cfg

class TestVitalWriteObjectTrackSet(TestVitalAlgorithmBasic, TestCase):


  def setUp(self):
    modules.load_known_modules()
    self.instance = WriteObjectTrackSet.create("SimpleImageObjectDetector")
    self.abstract_algo = WriteObjectTrackSet

  # Test write_set function with our simple class instance
  # When no argument is passed, it raises TypeError
  @nose.tools.raises(TypeError)
  def test_empty_write_set(self):
    self.instance.write_set()


  @nose.tools.raises(TypeError)
  def test_empty_open(self):
    self.instance.open()


  def test_open(self):
    nose.tools.ok_(not self.instance.buff_is_open, "buffer initialized as open")
    self.instance.open("dummy_wots_filename.txt")
    nose.tools.ok_(self.instance.buff_is_open, "buffer closed after open() call")


  def test_close(self):
    self.instance.open("dummy_wots_filename.txt") #buff_is_open is True
    # now close it
    self.instance.close()
    nose.tools.ok_(not self.instance.buff_is_open, "buffer open after close() call")


  def test_write_set(self):
    ots = ObjectTrackSet()
    self.instance.write_set(ots)
    nose.tools.ok_(self.instance.buff == "0", "content written doesn't match expected")










