// Copyright (C) 2010 by Thomas Moulard, CNRS.
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
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_UTIL_ASSERTION_HH
# define HPP_UTIL_ASSERTION_HH
# include <hpp/util/config.hh>
# include <hpp/util/exception.hh>

// If debug mode is disabled and assertions are not already
// disabled, disable them automatically.
# if (defined HPP_DEBUG) && (!defined HPP_ENABLE_ASSERTIONS)
#  define HPP_ENABLE_ASSERTIONS
# endif // (!defined HPP_DEBUG) && (!defined HPP_ENABLE_ASSERTIONS)

namespace hpp
{
  HPP_MAKE_EXCEPTION (HPP_UTIL_DLLAPI, AssertionError);
} // end of namespace hpp.

/// \brief Define HPP_ASSERT.
///
/// Throw an ::hpp::AssertionError if macro argument evaluates to
/// false.
# ifdef HPP_ENABLE_ASSERTIONS
#  define HPP_ASSERT(CONDITION)					\
  do {								\
    bool _x = static_cast<bool>(CONDITION);					\
    if (!_x)							\
      HPP_THROW_EXCEPTION					\
	(::hpp::AssertionError,					\
	 #CONDITION " evaluates to false");			\
  } while (0)
# else
#  define HPP_ASSERT(CONDITION)
# endif // HPP_ENABLE_ASSERTIONS

/// \brief Define macro for precondition checking.
# define HPP_PRECONDITION(CONDITION) HPP_ASSERT (CONDITION)

#endif //! HPP_UTIL_ASSERTION_HH
