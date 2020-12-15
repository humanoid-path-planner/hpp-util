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

#include <hpp/util/serialization.hh>

template<typename T>
int run_test_tpl ()
{
  std::stringstream ss;
  T* t(new T(10));
  {
    hpp::serialization::xml_oarchive oa(ss);
    oa << boost::serialization::make_nvp("t", t);
  }
  std::cout << ss.str() << std::endl;
  T* t_r = NULL;
  {
    hpp::serialization::xml_iarchive ia(ss);
    ia >> boost::serialization::make_nvp("t", t_r);
  }

  if (t_r == NULL || t_r->i_ != t->i_) {
    std::cerr << "Failed to deserialize " << hpp::serialization::guid<T>() << " class" << std::endl;
    return TEST_FAILED;
  }
  delete t;
  return TEST_SUCCEED;
}

int run_test_bar (bool check_throw)
{
  std::unique_ptr<Foo> foo (new Foo(1));
  std::stringstream ss;
  Bar* t(new Bar(10));
  {
    hpp::serialization::xml_oarchive oa(ss);
    oa.insert("foo", foo.get());
    oa.initialize();
    oa << boost::serialization::make_nvp("t", t);
  }
  std::cout << ss.str() << std::endl;
  Bar* t_r = NULL;
  bool caught_error;
  {
    hpp::serialization::xml_iarchive ia(ss);
    if (!check_throw)
      ia.insert("foo", foo.get());
    else
      ia.insert("foo", new Bar(0));
    try {
      caught_error=true;
      ia.initialize();
      caught_error=false;
      ia >> boost::serialization::make_nvp("t", t_r);
    } catch (const std::invalid_argument& e) {
      std::cerr << e.what() << std::endl;
    }
  }
  if (check_throw != caught_error) return TEST_FAILED;

  if (check_throw && t_r != NULL) {
    std::cerr << "Deserialize Bar class while it shouldn't" << std::endl;
    return TEST_FAILED;
  }
  if (!check_throw) {
    if (t_r->f_ != foo.get()) {
      std::cerr << "Failed to deserialize Bar::f_ Foo pointer" << std::endl;
      return TEST_FAILED;
    }
    if (t_r == NULL || t_r->i_ != t->i_) {
      std::cerr << "Failed to deserialize Bar class" << std::endl;
      return TEST_FAILED;
    }
  }
  delete t;
  return TEST_SUCCEED;
}

struct S1 { virtual ~S1() = default; };
struct S2 : S1 {};

BOOST_CLASS_EXPORT_KEY(S1)
BOOST_CLASS_EXPORT_KEY(S2)

int run_test_holder_inheritance()
{
  using namespace hpp::serialization;
  archive_ptr_holder aph;
  S2 s2;
  aph.insert<S1>("s1", &s2);
  aph.insertChildClass<S1>("s2", &s2);

  aph.template get<S1>("s1", true);
  aph.getChildClass<S1, S2>("s2", true);
  S1* s1 = aph.template get<S1>("s2", false);
  if (s1 == NULL) {
    std::cerr << "Failed to cast S2 into S1" << std::endl;
    return TEST_FAILED;
  }
  return TEST_SUCCEED;
}

int run_test_archive_parents()
{
  using namespace hpp::serialization;
  struct P1 {};
  struct P2 {};
  typedef archive_tpl<boost::archive::xml_iarchive, P1, P2> type;
  std::stringstream ss;
  type t (ss);
  (void) t;
  return TEST_SUCCEED;
}

int run_test ()
{
  if (run_test_tpl<Foo    >()      == TEST_FAILED) return TEST_FAILED;
  if (run_test_bar         (true)  == TEST_FAILED) return TEST_FAILED;
  if (run_test_bar         (false) == TEST_FAILED) return TEST_FAILED;
  if (run_test_tpl<FooFree>()      == TEST_FAILED) return TEST_FAILED;
  if (run_test_tpl<BarFree>()      == TEST_FAILED) return TEST_FAILED;
  if (run_test_holder_inheritance()== TEST_FAILED) return TEST_FAILED;
  return TEST_SUCCEED;
}

GENERATE_TEST ()
