//
// Copyright (C) 2016 by Joseph Mirabel, CNRS.
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

#ifndef HPP_UTIL_EXCEPTION_FACTORY_HH
#define HPP_UTIL_EXCEPTION_FACTORY_HH

#include <hpp/util/config.hh>
#include <sstream>

namespace hpp {
/// \cond
struct ThrowException {};

template <typename exception>
struct ExceptionFactory;

namespace internal {
template <typename exception, typename In>
struct conditional_insertion_operator {
  typedef ExceptionFactory<exception>& type;

  static inline type run(ExceptionFactory<exception>& be, const In& t) {
    be.ss << t;
    return be;
  }
};
}  // namespace internal
/// \endcond

/// \brief Class to ease exception creation.
///
/// You can use equivalently
/// \code
///   throw ::hpp::ExceptionFactory<std::runtime_error>() << "message" <<
///   variable << ::hpp::ThrowException();
/// \endcode
/// or
/// \code
///   HPP_THROW(std::runtime_error>, "message" << variable);
/// \endcode
template <typename exception>
struct HPP_UTIL_DLLAPI ExceptionFactory {
  std::stringstream ss;

  template <typename T>
  inline typename internal::conditional_insertion_operator<exception, T>::type
  operator<<(const T& t) {
    return internal::conditional_insertion_operator<exception, T>::run(*this,
                                                                       t);
  }
};

/// \cond
// ----------------------------------------
// ExceptionFactory - template specialization
// ----------------------------------------
namespace internal {
template <typename exception>
struct conditional_insertion_operator<exception, ThrowException> {
  typedef exception type;

  static inline type run(ExceptionFactory<exception>& be,
                         const ThrowException&) {
    return exception(be.ss.str().c_str());
  }
};
}  // namespace internal
/// \endcond
}  // end of namespace hpp.

/// \addtogroup hpp_util_exceptions
/// \{

/// \brief Throw an exception of type using MSG as a string stream
/// \code
///   HPP_THROW(std::runtime_error, "message" << variable);
/// \endcode
#define HPP_THROW(TYPE, MSG) \
  throw ::hpp::ExceptionFactory<TYPE>() << MSG << ::hpp::ThrowException()

/// \brief Throw an exception of type using MSG as a string stream
/// \code
///   HPP_THROW_WITH_LINEINFO(std::runtime_error>, "message" << variable);
/// \endcode
#define HPP_THROW_WITH_LINEINFO(TYPE, MSG) \
  HPP_THROW(TYPE, MSG << " at " << __FILE__ << ":" << __LINE__)

/// \}

#endif  //! HPP_UTIL_EXCEPTION_FACTORY_HH
