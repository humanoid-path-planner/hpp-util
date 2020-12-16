// Copyright (c) 2016, Joseph Mirabel
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

#include "config.h"

#include <iostream>
#include <hpp/util/debug.hh>

#include "common.hh"

using namespace hpp::debug;

int run_test ()
{
  ConsoleOutput console;
  JournalOutput out ("debug.test.log");
  Channel channel ("TEST", { &out, &console });
  for (int i = 0; i < 100; ++i) {
    std::stringstream ss;
    ss << i << hpp::iendl;
    channel.write (__FILE__, __LINE__, __PRETTY_FUNCTION__, ss);
  }
  return 0;
}

GENERATE_TEST ()
