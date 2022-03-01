// Copyright (C) 2010 by Thomas Moulard.
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

// Make sure assertions are enabled (otherwise this test does not make
// sense).
#ifndef HPP_ENABLE_ASSERTIONS
# define HPP_ENABLE_ASSERTIONS
#endif // !HPP_ENABLE_ASSERTIONS

#include "config.h"

#include <cassert>
#include <iostream>
#include <hpp/util/assertion.hh>

#include "common.hh"

int run_test ();
int my_plus_function (int a, int b);
int my_broken_plus_function (int a, int b);

int my_plus_function (int a, int b)
{
  // This algorithm does not work with negative numbers.
  HPP_PRECONDITION (a >= 0);
  HPP_PRECONDITION (b >= 0);

  int res = 0, expected = a + b;

  res = b;
  while (a > 0)
    --a, ++res;

  // This algorithm should have computed a + b.
  HPP_ASSERT (res == expected);

  return res;
}

int my_broken_plus_function (int a, int b)
{
  // This algorithm does not work with negative numbers.
  HPP_PRECONDITION (a >= 0);
  HPP_PRECONDITION (b >= 0);

  int res = 0, expected = a + b;

  res = b; // This is wrong.

  // This algorithm should have computed a + b.
  HPP_ASSERT (res == expected);

  return res;
}

int run_test ()
{
  // Assertion.
  try
    {
      int i = 4;
      HPP_ASSERT (i > 2);
      HPP_ASSERT (i < 3);
    }
  catch (::hpp::AssertionError& assertionError)
    {
      std::cout << assertionError << std::endl;
    }

  // Good calls.
  my_plus_function (4, 5);
  my_plus_function (7, 9);

  // Check for precondition failure.
  try
    {
      my_plus_function (-2, 5);
    }
  catch (::hpp::AssertionError& assertionError)
    {
      std::cout << assertionError << std::endl;
    }

  // Check for postcondition failure.
  try
    {
      my_broken_plus_function (3, 5);
    }
  catch (::hpp::AssertionError& assertionError)
    {
      std::cout << assertionError << std::endl;
    }

  return 0;
}

GENERATE_TEST ()
