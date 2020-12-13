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

#include <hpp/util/serialization-fwd.hh>

class Foo {
  public:
    Foo(int i) : i_ (i) {};
    int i_;

  private:
    Foo() {}
    HPP_SERIALIZABLE();
};

BOOST_CLASS_EXPORT_KEY(Foo)

class Bar {
  public:
    Bar(int i) : i_ (i) {};
    int i_;
    Foo* f_;

  private:
    Bar() {}
    HPP_SERIALIZABLE_SPLIT();
};

BOOST_CLASS_EXPORT_KEY(Bar)

class FooFree {
  public:
    FooFree(int i) : i_ (i) {};
    int i_;

    FooFree() {}
};

HPP_SERIALIZABLE_FREE(FooFree)

class BarFree {
  public:
    BarFree(int i) : i_ (i) {};
    int i_;

    BarFree() {}
};

HPP_SERIALIZABLE_SPLIT_FREE(BarFree)
