// Copyright (c) 2016, Joseph Mirabel
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
HPP_DEFINE_TIMECOUNTER(testCounter2);

int run_test ()
{
  int N = 10;
  logging.benchmark = Channel ("BENCHMARK", { &logging.console });
  for (int i = 0; i < N; ++i) {
    HPP_START_TIMECOUNTER(testCounter);
    int k = 1 + (std::rand()%10);
    // std::cout << k << std::endl;
    f(k);
    HPP_STOP_TIMECOUNTER(testCounter);
    HPP_DISPLAY_LAST_TIMECOUNTER(testCounter);
  }
  HPP_DISPLAY_TIMECOUNTER(testCounter);
  for (int i = 0; i < N; ++i) {
    HPP_SCOPE_TIMECOUNTER(testCounter2);
    int k = 1 + (std::rand()%10);
    // std::cout << k << std::endl;
    f(k);
    HPP_DISPLAY_LAST_TIMECOUNTER(testCounter2);
  }
  HPP_DISPLAY_TIMECOUNTER(testCounter2);
  return 0;
}

GENERATE_TEST ()
