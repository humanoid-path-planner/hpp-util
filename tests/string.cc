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

#include <iostream>
#include <hpp/util/string.hh>

#include "common.hh"

using namespace hpp::util;

int run_test ()
{
  std::string str("avq  vfb\tcfdsqf\ndfqs;");

  string_split(str.begin(), str.end(), " \t\n",
      [](decltype(str.begin()) begin, decltype(str.begin()) end) {
        std::cout << std::string(&(*begin), std::distance(begin, end)) << "\n";
        return false;
      });

  if ( iequal("abd", "AB"))  return TEST_FAILED;
  if (!iequal("abd", "ABd")) return TEST_FAILED;
  if ( iequal("abd", "Acd")) return TEST_FAILED;

  return TEST_SUCCEED;
}

GENERATE_TEST ()
