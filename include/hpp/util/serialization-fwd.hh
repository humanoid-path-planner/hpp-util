//
// Copyright (c) 2020 CNRS
// Authors: Joseph Mirabel
//
// This file is part of hpp-util
// hpp-util is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-util is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-util  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef HPP_UTIL_SERIALIZATION_FWD_HH
#define HPP_UTIL_SERIALIZATION_FWD_HH

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/export.hpp>

namespace boost {
namespace serialization {
class access;
} // namespace serialization
} // namespace boost

/// Macro that should be put in a serializable class
/// It declares function \c serialize.
/// \note an empty constructor (that can leave the object unitialized) must exist.
#define HPP_SERIALIZABLE()                                                     \
  friend class boost::serialization::access;                                   \
  /** Allow serialization of the class using \c boost::serialization. */       \
  template<class Archive>                                                      \
  void serialize(Archive & ar, const unsigned int version)

/// Macro that should be put in a serializable class
/// It declares functions \c serialize, \c load and \c save. The two last
/// must be implemented by the caller.
/// \note an empty constructor (that can leave the object unitialized) must exist.
#define HPP_SERIALIZABLE_SPLIT()                                               \
    BOOST_SERIALIZATION_SPLIT_MEMBER()                                         \
    friend class boost::serialization::access;                                 \
    /** Allow to save class using \c boost::serialization. */                  \
    template<class Archive>                                                    \
    void save(Archive & ar, const unsigned int version) const;                 \
    /** Allow to load class using \c boost::serialization. */                  \
    template<class Archive>                                                    \
    void load(Archive & ar, const unsigned int version)

/// Macro that should be put in a serializable class, using a free function
/// It declares free function \c serialize.
/// This macro must be called outside of any namespace.
/// \note an empty constructor (that can leave the object unitialized) must exist.
#define HPP_SERIALIZABLE_FREE(type)                                            \
  namespace boost { namespace serialization {                                  \
  template<class Archive>                                                      \
  void serialize(Archive & ar, type& t, const unsigned int version);           \
  }}


/// Macro that should be put in a serializable class, using a free function
/// It declares free functions \c serialize, \c load and \c save. The two last
/// must be implemented by the caller.
/// This macro must be called outside of any namespace.
/// \note an empty constructor (that can leave the object unitialized) must exist.
#define HPP_SERIALIZABLE_SPLIT_FREE(type)                                      \
  HPP_SERIALIZABLE_FREE(type)

#endif // HPP_UTIL_SERIALIZATION_FWD_HH
