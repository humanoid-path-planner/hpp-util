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

#include <sstream>

#include "config.h"
#include "common.hh"
#include "serialization.hh"

#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>

int run_test ()
{
  std::stringstream ss;
  Foo foo(10);
  Bar bar(20);
  {
    boost::archive::polymorphic_xml_oarchive oa(ss);
    oa << boost::serialization::make_nvp("foo", foo);
    oa << boost::serialization::make_nvp("bar", bar);
  }
  Foo* foo_r = NULL;
  Bar* bar_r = NULL;
  {
    boost::archive::polymorphic_xml_iarchive ia(ss);
    ia >> boost::serialization::make_nvp("foo", foo_r);
    ia >> boost::serialization::make_nvp("bar", bar_r);
  }

  if (foo_r == NULL || foo_r->i_ != foo.i_) return TEST_FAILED;
  if (bar_r == NULL || bar_r->i_ != bar.i_) return TEST_FAILED;
  return TEST_SUCCEED;
}

GENERATE_TEST ()
