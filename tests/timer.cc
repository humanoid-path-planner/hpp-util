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

#include <boost/assign/list_of.hpp>
#include <cstdlib>

#include "config.h"

#define HPP_ENABLE_BENCHMARK 1
#include <hpp/util/timer.hh>

#include "common.hh"

using namespace hpp::debug;

// the function f() does some time-consuming work
void f(const int extra)
{
    volatile double d = 0;
    for(int n=0; n<extra * 1000; ++n)
       for(int m=0; m<1000; ++m)
           d += d*n*m;
}

HPP_DEFINE_TIMECOUNTER(testCounter);

int run_test ()
{
  logging.benchmark = Channel ("BENCHMARK", boost::assign::list_of<Output*> (&logging.console));
  for (int i = 0; i < 10; ++i) {
    HPP_START_TIMECOUNTER(testCounter);
    int k = 1 + (std::rand()%10);
    // std::cout << k << std::endl;
    f(k);
    HPP_STOP_TIMECOUNTER(testCounter);
    HPP_DISPLAY_LAST_TIMECOUNTER(testCounter);
  }
  HPP_DISPLAY_TIMECOUNTER(testCounter);
  return 0;
}

GENERATE_TEST ()
