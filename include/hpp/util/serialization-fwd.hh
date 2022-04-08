//
// Copyright (c) 2020 CNRS
// Authors: Joseph Mirabel
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

#ifndef HPP_UTIL_SERIALIZATION_FWD_HH
#define HPP_UTIL_SERIALIZATION_FWD_HH

#include <boost/serialization/export.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/split_member.hpp>

namespace boost {
namespace serialization {
class access;
}  // namespace serialization
}  // namespace boost

/// Macro that should be put in a serializable class
/// It declares function \c serialize.
/// \note an empty constructor (that can leave the object unitialized) must
/// exist.
#define HPP_SERIALIZABLE()                                               \
  friend class boost::serialization::access;                             \
  /** Allow serialization of the class using \c boost::serialization. */ \
  template <class Archive>                                               \
  void serialize(Archive& ar, const unsigned int version)

/// Macro that should be put in a serializable class
/// It declares functions \c serialize, \c load and \c save. The two last
/// must be implemented by the caller.
/// \note an empty constructor (that can leave the object unitialized) must
/// exist.
#define HPP_SERIALIZABLE_SPLIT()                            \
  BOOST_SERIALIZATION_SPLIT_MEMBER()                        \
  friend class boost::serialization::access;                \
  /** Allow to save class using \c boost::serialization. */ \
  template <class Archive>                                  \
  void save(Archive& ar, const unsigned int version) const; \
  /** Allow to load class using \c boost::serialization. */ \
  template <class Archive>                                  \
  void load(Archive& ar, const unsigned int version)

/// Macro that should be put in a serializable class, using a free function
/// It declares free function \c serialize.
/// This macro must be called outside of any namespace.
/// \note an empty constructor (that can leave the object unitialized) must
/// exist.
#define HPP_SERIALIZABLE_FREE(type)                                 \
  namespace boost {                                                 \
  namespace serialization {                                         \
  template <class Archive>                                          \
  void serialize(Archive& ar, type& t, const unsigned int version); \
  }                                                                 \
  }

/// Macro that should be put in a serializable class, using a free function
/// It declares free functions \c serialize, \c load and \c save. The two last
/// must be implemented by the caller.
/// This macro must be called outside of any namespace.
/// \note an empty constructor (that can leave the object unitialized) must
/// exist.
#define HPP_SERIALIZABLE_SPLIT_FREE(type) HPP_SERIALIZABLE_FREE(type)

#endif  // HPP_UTIL_SERIALIZATION_FWD_HH
