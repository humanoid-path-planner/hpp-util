// Copyright (c) 2020, Joseph Mirabel
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-util.
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
// hpp-util. If not, see <http://www.gnu.org/licenses/>.

#include <hpp/util/serialization.hh>

#include "serialization.hh"

BOOST_CLASS_EXPORT(Foo)

template<class Archive>
void Foo::serialize(Archive & ar, const unsigned int version)
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", i_);
}

HPP_SERIALIZATION_IMPLEMENT(Foo);

BOOST_CLASS_EXPORT(Bar)

template<class Archive>
void Bar::load(Archive & ar, const unsigned int version)
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", i_);
}

template<class Archive>
void Bar::save(Archive & ar, const unsigned int version) const
{
  (void) version;
  ar & hpp::serialization::make_nvp("i", i_);
}

HPP_SERIALIZATION_SPLIT_IMPLEMENT(Bar);
