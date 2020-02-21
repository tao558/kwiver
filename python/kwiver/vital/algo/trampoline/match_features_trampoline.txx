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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
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

/**
 * \file match_features_trampoline.txx
 *
 * \brief trampoline for overriding virtual functions of
 *        algorithm_def<match_features> and match_features
 */

#ifndef MATCH_FEATURES_TRAMPOLINE_TXX
#define MATCH_FEATURES_TRAMPOLINE_TXX


#include <python/kwiver/vital/util/pybind11.h>
#include <python/kwiver/vital/algo/trampoline/algorithm_trampoline.txx>
#include <vital/algo/match_features.h>

namespace kwiver {
namespace vital  {
namespace python {

template < class algorithm_def_mf_base=
            kwiver::vital::algorithm_def<
              kwiver::vital::algo::match_features > >
class algorithm_def_mf_trampoline :
      public algorithm_trampoline<algorithm_def_mf_base>
{
  public:
    using algorithm_trampoline<algorithm_def_mf_base>::algorithm_trampoline;

    std::string type_name() const override
    {
      VITAL_PYBIND11_OVERLOAD(
        std::string,
        kwiver::vital::algorithm_def<kwiver::vital::algo::match_features>,
        type_name,
      );
    }
};


template< class match_features_base=
                kwiver::vital::algo::match_features >
class match_features_trampoline :
      public algorithm_def_mf_trampoline< match_features_base >
{
  public:
    using algorithm_def_mf_trampoline< match_features_base>::
              algorithm_def_mf_trampoline;

    kwiver::vital::match_set_sptr
    match( kwiver::vital::feature_set_sptr feat1,
           kwiver::vital::descriptor_set_sptr desc1,
           kwiver::vital::feature_set_sptr feat2,
           kwiver::vital::descriptor_set_sptr desc2 ) const override
    {
      VITAL_PYBIND11_OVERLOAD_PURE(
        kwiver::vital::match_set_sptr,
        kwiver::vital::algo::match_features,
        match,
        feat1,
        desc1,
        feat2,
        desc2
      );
    }
};

}
}
}

#endif
