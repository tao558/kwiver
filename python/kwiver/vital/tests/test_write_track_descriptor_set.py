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

Tests for write track descriptor set interface class
"""
import nose.tools
import os

from kwiver.vital.algo import WriteTrackDescriptorSet
from kwiver.vital.modules import modules
from kwiver.vital.config import config
from unittest import TestCase
from unittest.mock import Mock
from kwiver.vital.tests.helpers import generate_dummy_config


class TestVitalWriteTrackDescriptorSet(TestCase):

  def setUp(self):
    modules.load_known_modules()
    self.wtds = WriteTrackDescriptorSet.create("SimpleWriteTrackDescriptorSet")


# Display all the registered write track descriptor sets
  def test_registered_names(self):
    modules.load_known_modules()
    registered_wtds_names = WriteTrackDescriptorSet.registered_names()
    print("All write track descriptor sets")
    for name in registered_wtds_names:
        print(" " + name)


  # Test create function
  # For an invalid value it raises RuntimeError
  @nose.tools.raises(RuntimeError)
  def test_bad_create(self):
    # Should fail to create an algorithm without a factory
    WriteTrackDescriptorSet.create("NonExistantAlgorithm")

  # For a registered write track descriptor set it returns an instance of the implementation
  def test_create(self):
    modules.load_known_modules()
    registered_wtds_name = WriteTrackDescriptorSet.registered_names()[0]
    nose.tools.ok_(registered_wtds_name is not None,
                    "No instance returned from the factory method")


  # Test write_set function with our simple class instance
  # When no argument is passed, it raises TypeError
  @nose.tools.raises(TypeError)
  @nose.tools.with_setup(setup = setUp)
  def test_empty_write_set(self):
    self.wtds.write_set()


  @nose.tools.raises(TypeError)
  @nose.tools.with_setup(setUp)
  def test_empty_open(self):
    self.wtds.open()


  @nose.tools.with_setup(setup = setUp)
  def test_open(self):
    nose.tools.ok_(not self.wtds.buff_is_open, "buffer initialized as open")
    self.wtds.open("dummy_wtds_filename.txt")
    nose.tools.ok_(self.wtds.buff_is_open, "buffer closed after open() call")


  @nose.tools.with_setup(setup = setUp)
  def test_close(self):
    self.wtds.open("dummy_wtds_filename.txt") #buff_is_open is True
    # now close it
    self.wtds.close()
    nose.tools.ok_(not self.wtds.buff_is_open, "buffer open after close() call")

  @nose.tools.with_setup(setup = setUp)
  def test_write_set(self):
    self.wtds.open("dummy_wtds_filename.txt")
    track_descriptor_mock = Mock()
    self.wtds.write_set([track_descriptor_mock])
    track_descriptor_mock.method.assert_called_once_with()
