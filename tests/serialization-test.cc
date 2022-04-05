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

#include "serialization.hh"

#include <hpp/util/serialization.hh>
#include <sstream>

#include "common.hh"
#include "config.h"

template <typename T>
int run_test_tpl() {
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
    std::cerr << "Failed to deserialize " << hpp::serialization::guid<T>()
              << " class" << std::endl;
    return TEST_FAILED;
  }
  delete t;
  return TEST_SUCCEED;
}

int run_test_bar(bool check_throw) {
  std::unique_ptr<Foo> foo(new Foo(1));
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
      caught_error = true;
      ia.initialize();
      caught_error = false;
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

struct S1 {
  virtual ~S1() = default;
};
struct S2 : S1 {};

BOOST_CLASS_EXPORT_KEY(S1)
BOOST_CLASS_EXPORT_KEY(S2)

int run_test_holder_inheritance() {
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

int run_test_archive_parents() {
  using namespace hpp::serialization;
  struct P1 {};
  struct P2 {};
  typedef archive_tpl<boost::archive::xml_iarchive, P1, P2> type;
  std::stringstream ss;
  type t(ss);
  (void)t;
  return TEST_SUCCEED;
}

int run_test() {
  if (run_test_tpl<Foo>() == TEST_FAILED) return TEST_FAILED;
  if (run_test_bar(true) == TEST_FAILED) return TEST_FAILED;
  if (run_test_bar(false) == TEST_FAILED) return TEST_FAILED;
  if (run_test_tpl<FooFree>() == TEST_FAILED) return TEST_FAILED;
  if (run_test_tpl<BarFree>() == TEST_FAILED) return TEST_FAILED;
  if (run_test_holder_inheritance() == TEST_FAILED) return TEST_FAILED;
  return TEST_SUCCEED;
}

GENERATE_TEST()
