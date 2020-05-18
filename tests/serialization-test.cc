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

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

template<typename T>
int run_test_tpl ()
{
  std::stringstream ss;
  T t(10);
  {
    boost::archive::xml_oarchive oa(ss);
    oa << boost::serialization::make_nvp("t", t);
  }
  Foo* t_r = NULL;
  {
    boost::archive::xml_iarchive ia(ss);
    ia >> boost::serialization::make_nvp("t", t_r);
  }

  if (t_r == NULL || t_r->i_ != t.i_) return TEST_FAILED;
  return TEST_SUCCEED;
}

int run_test ()
{
  if (run_test_tpl<Foo    >() == TEST_FAILED) return TEST_FAILED;
  if (run_test_tpl<Bar    >() == TEST_FAILED) return TEST_FAILED;
  if (run_test_tpl<FooFree>() == TEST_FAILED) return TEST_FAILED;
  if (run_test_tpl<BarFree>() == TEST_FAILED) return TEST_FAILED;
  return TEST_SUCCEED;
}

GENERATE_TEST ()
