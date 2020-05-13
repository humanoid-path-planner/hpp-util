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

#ifndef HPP_UTIL_SERIALIZATION_HH
#define HPP_UTIL_SERIALIZATION_HH

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/nvp.hpp>

#define _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type,archive,arg)                   \
  template void type load<archive##_iarchive>(archive##_iarchive& ar,          \
      arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg)))              \
      const unsigned int ver);                                                 \
  template void type save<archive##_oarchive>(archive##_oarchive& ar,          \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(arg),,const) arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg))) \
    const unsigned int ver) BOOST_PP_IF(BOOST_PP_IS_EMPTY(arg),const,)

#define _HPP_SERIALIZATION_IMPLEMENT(type,archive,arg)                         \
    template void type serialize<archive##_iarchive>(archive##_iarchive& ar,   \
        arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg)))            \
        const unsigned int ver);                                               \
    template void type serialize<archive##_oarchive>(archive##_oarchive& ar,   \
        arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg)))            \
        const unsigned int ver) 

#define HPP_SERIALIZATION_SPLIT_IMPLEMENT(type)                                \
    _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type::,boost::archive::polymorphic,);   \
    _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type::,boost::archive::xml,);           \
    _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type::,boost::archive::text,);          \
    _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type::,boost::archive::binary,)

#define HPP_SERIALIZATION_IMPLEMENT(type)                                      \
    _HPP_SERIALIZATION_IMPLEMENT(type::,boost::archive::polymorphic,);         \
    _HPP_SERIALIZATION_IMPLEMENT(type::,boost::archive::xml,);                 \
    _HPP_SERIALIZATION_IMPLEMENT(type::,boost::archive::text,);                \
    _HPP_SERIALIZATION_IMPLEMENT(type::,boost::archive::binary,)

#define HPP_SERIALIZATION_FREE_IMPLEMENT(type)                                 \
    namespace boost { namespace serialization {                                \
    _HPP_SERIALIZATION_IMPLEMENT(,archive::polymorphic,type& t);               \
    _HPP_SERIALIZATION_IMPLEMENT(,archive::xml,type& t);                       \
    _HPP_SERIALIZATION_IMPLEMENT(,archive::text,type& t);                      \
    _HPP_SERIALIZATION_IMPLEMENT(,archive::binary,type& t);                    \
    }}

#define HPP_SERIALIZATION_SPLIT_FREE_IMPLEMENT(type)                           \
  namespace boost { namespace serialization {                                  \
  template<class Archive>                                                      \
  void serialize(Archive & ar, type& t, const unsigned int version) {          \
    split_free(ar, t, version);                                                \
  }                                                                            \
  _HPP_SERIALIZATION_IMPLEMENT(,archive::polymorphic,type& t);               \
  _HPP_SERIALIZATION_IMPLEMENT(,archive::xml,type& t);                       \
  _HPP_SERIALIZATION_IMPLEMENT(,archive::text,type& t);                      \
  _HPP_SERIALIZATION_IMPLEMENT(,archive::binary,type& t);                    \
  }}

namespace hpp {
namespace serialization {
using boost::serialization::make_nvp;
} // namespace util
} // namespace hpp

#endif // HPP_UTIL_SERIALIZATION_HH
