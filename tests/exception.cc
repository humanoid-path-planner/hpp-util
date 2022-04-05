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

#include <cassert>
#include <hpp/util/exception.hh>
#include <iostream>

#include "common.hh"
#include "config.h"

HPP_MAKE_EXCEPTION_NO_QUALIFIER(CustomException);

int run_test();

int run_test() {
  ::hpp::Exception exception("put your message here", "filename", 0);
  std::cout << exception << std::endl;

  try {
    HPP_THROW_EXCEPTION_("this exception should be catched");
    assert(0);
  } catch (::hpp::Exception& exception) {
    std::cout << exception << std::endl;
  }

  try {
    HPP_THROW_EXCEPTION(::hpp::Exception, "this exception should be catched");
    assert(0);
  } catch (::hpp::Exception& exception) {
    std::cout << exception << std::endl;
  }

  try {
    HPP_THROW_EXCEPTION(CustomException,
                        "this custom exception should be catched");
    assert(0);
  } catch (::hpp::Exception& exception) {
    std::cout << exception << std::endl;
  }
  return 0;
}

GENERATE_TEST()
