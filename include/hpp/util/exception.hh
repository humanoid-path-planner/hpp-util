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

/// \file

#ifndef HPP_UTIL_EXCEPTION_HH
#define HPP_UTIL_EXCEPTION_HH
#include <hpp/util/config.hh>
#include <iosfwd>
#include <stdexcept>
#include <string>

namespace hpp {
/// \brief Main exception class for HPP.
///
/// All exceptions thrown in HPP must inherit this class.
class HPP_UTIL_DLLAPI Exception : public std::exception {
 public:
  Exception(const std::string& message, const std::string& file,
            unsigned line) throw();
  ~Exception() throw();
  Exception(const Exception& exception) throw();
  Exception& operator=(const Exception& exception) throw();

  virtual const char* what() const throw();

  /// \brief Display the exception on the specified output stream.
  ///
  /// \param o output stream used for display
  /// \return output stream
  virtual std::ostream& print(std::ostream& o) const throw();

 private:
  std::string message_;
  std::string file_;
  unsigned line_;
};

/// \brief Override operator<< to handle exception display.
///
/// \param o output stream used for display
/// \param exception exception to be displayed
/// \return output stream
HPP_UTIL_DLLAPI std::ostream& operator<<(std::ostream& o,
                                         const Exception& exception);

}  // end of namespace hpp.

/// \brief Launch a HPP exception.
#define HPP_THROW_EXCEPTION_(MSG) \
  throw ::hpp::Exception(MSG, __FILE__, __LINE__)

/// \brief Launch a HPP exception (generic macro).
#define HPP_THROW_EXCEPTION(TYPE, MSG) throw TYPE(MSG, __FILE__, __LINE__)

/// \brief Define a custom exception.
#define HPP_MAKE_EXCEPTION(EXTRA_QUALIFIER, TYPE)                            \
  class EXTRA_QUALIFIER TYPE : public ::hpp::Exception {                     \
   public:                                                                   \
    TYPE(const std::string& message, const std::string& file, unsigned line) \
    throw() : ::hpp::Exception(message, file, line) {}                       \
  }

/// \brief Define a custom exception without extra qualifier.
#define HPP_MAKE_EXCEPTION_NO_QUALIFIER(TYPE)                                \
  class TYPE : public ::hpp::Exception {                                     \
   public:                                                                   \
    TYPE(const std::string& message, const std::string& file, unsigned line) \
    throw() : ::hpp::Exception(message, file, line) {}                       \
  }

#endif  //! HPP_UTIL_EXCEPTION_HH
