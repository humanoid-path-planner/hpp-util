// Copyright (c) 2020, Joseph Mirabel
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.

#include <hpp/util/serialization.hh>

#include "serialization.hh"

BOOST_CLASS_EXPORT_IMPLEMENT(Foo)

template<class Archive>
void Foo::serialize(Archive & ar, const unsigned int version)
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", i_);
}

HPP_SERIALIZATION_IMPLEMENT(Foo);

BOOST_CLASS_EXPORT_IMPLEMENT(Bar)

template<class Archive>
void Bar::load(Archive & ar, const unsigned int version)
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", i_);
  f_ = hpp::serialization::cast(ar).template get<Foo>("foo", true);
}

template<class Archive>
void Bar::save(Archive & ar, const unsigned int version) const
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", i_);
}

HPP_SERIALIZATION_SPLIT_IMPLEMENT(Bar);

namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive & ar, FooFree& foo, const unsigned int version)
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", foo.i_);
}

template<class Archive>
void load(Archive & ar, BarFree& bar, const unsigned int version)
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", bar.i_);
}

template<class Archive>
void save(Archive & ar, const BarFree& bar, const unsigned int version)
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", bar.i_);
}

}
}

HPP_SERIALIZATION_FREE_IMPLEMENT(FooFree)

HPP_SERIALIZATION_SPLIT_FREE_IMPLEMENT(BarFree)
