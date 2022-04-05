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

#include <hpp/util/serialization-fwd.hh>

class Foo {
 public:
  Foo(int i) : i_(i){};
  int i_;

 private:
  Foo() {}
  HPP_SERIALIZABLE();
};

BOOST_CLASS_EXPORT_KEY(Foo)

class Bar {
 public:
  Bar(int i) : i_(i){};
  int i_;
  Foo* f_;

 private:
  Bar() {}
  HPP_SERIALIZABLE_SPLIT();
};

BOOST_CLASS_EXPORT_KEY(Bar)

class FooFree {
 public:
  FooFree(int i) : i_(i){};
  int i_;

  FooFree() {}
};

HPP_SERIALIZABLE_FREE(FooFree)

class BarFree {
 public:
  BarFree(int i) : i_(i){};
  int i_;

  BarFree() {}
};

HPP_SERIALIZABLE_SPLIT_FREE(BarFree)
