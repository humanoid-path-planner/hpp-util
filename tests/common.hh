// Copyright (C) 2009 by Florent Lamiraux.
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


#ifndef TESTS_COMMON_HH
# define TESTS_COMMON_HH
# include <stdexcept>
# include <iostream>
# include "config.h"

static constexpr int TEST_FAILED = 10;
static constexpr int TEST_SUCCEED = 0;

# define GENERATE_TEST()                                \
  int                                                   \
  main (int argc, char** argv)                          \
  {                                                     \
    if (argc == 2                                       \
        && std::string (argv[1]) == "--version")        \
      {                                                 \
        std::cout << PACKAGE_STRING << std::endl;       \
        return 0;                                       \
      }                                                 \
                                                        \
    int status = 0;                                     \
    try                                                 \
      {                                                 \
        status = run_test ();                           \
      }                                                 \
    catch (std::runtime_error& e)                       \
      {                                                 \
        std::cerr << e.what () << std::endl;            \
        return 1;                                       \
      }                                                 \
    catch (...)                                         \
      {                                                 \
        std::cerr << "Unexpected error" << std::endl;   \
        return 2;                                       \
      }                                                 \
    return status;                                      \
  }

#define CHECK_FAILURE(EXCEPTION, CMD)           \
  {                                             \
    bool failed = true;                         \
    try                                         \
      {                                         \
        CMD;                                    \
      }                                         \
    catch (EXCEPTION&)                          \
      {                                         \
        failed = false;                         \
      }                                         \
    catch (...)                                 \
      {}                                        \
    if (failed)                                 \
      return TEST_FAILED;                       \
  }

#endif //! TESTS_COMMON_HH
