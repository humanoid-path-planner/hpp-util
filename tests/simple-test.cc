// Copyright (C) 2009 by Florent Lamiraux.
//
// This file is part of the hpp-util.
//
// hpp-util is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// hpp-util is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp-util.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include <iostream>
#include <hpp/util/debug.hh>
#include <hpp/util/version.hh>

#include "common.hh"


int run_test ();

int run_test ()
{
  if (hpp::util::checkVersion(HPP_UTIL_VERSION) != 0)
    return TEST_FAILED;
  return TEST_SUCCEED;
}

GENERATE_TEST ()
