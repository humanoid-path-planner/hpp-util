// Copyright (C) 2016 by Joseph Mirabel.
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

#include <cassert>
#include <hpp/util/exception-factory.hh>
#include <iostream>
#include <stdexcept>

#include "common.hh"
#include "config.h"

int run_test();

int run_test() {
  try {
    throw ::hpp::ExceptionFactory<std::runtime_error>()
        << "manually built std::runtime_error" << ::hpp::ThrowException();
    assert(0);
  } catch (const std::exception& exception) {
    std::cout << "Caught " << exception.what() << std::endl;
  }

  try {
    HPP_THROW(std::runtime_error, "std::runtime_error");
    assert(0);
  } catch (const std::exception& exception) {
    std::cout << "Caught " << exception.what() << std::endl;
  }

  try {
    double d = 12;
    std::string foo = "foo";
    HPP_THROW_WITH_LINEINFO(
        std::runtime_error,
        "std::runtime_error using operator<< " << foo << " " << d);
    assert(0);
  } catch (const std::exception& exception) {
    std::cout << "Caught " << exception.what() << std::endl;
  }
  return 0;
}

GENERATE_TEST()
