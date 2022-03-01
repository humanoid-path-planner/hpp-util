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

#include <iostream>

#ifdef HPP_LOG_EXCEPTION
# include "hpp/util/debug.hh"
#endif // HPP_LOG_EXCEPTION

#include "hpp/util/exception.hh"

namespace hpp
{
  Exception::Exception (const std::string& message,
			const std::string& file,
			unsigned line) throw ()
    : std::exception (),
      message_ (message),
      file_ (file),
      line_ (line)
  {
    // Allow to transparently log created exceptions.
#ifdef HPP_LOG_EXCEPTION
    hppDout (info, *this);
#endif // HPP_LOG_EXCEPTION
  }

  Exception::~Exception () throw ()
  {}

  Exception::Exception (const Exception& exception) throw ()
    : std::exception (),
      message_ (exception.message_),
      file_ (exception.file_),
      line_ (exception.line_)
  {}

  Exception&
  Exception::operator= (const Exception& exception) throw ()
  {
    if (&exception == this)
      return *this;

    message_ = exception.message_;
    file_  = exception.file_;
    line_  = exception.line_;
    return *this;
  }

  const char*
  Exception::what () const throw ()
  {
    //FIXME: display line and file too.
    return message_.c_str ();
  }

  std::ostream&
  Exception::print (std::ostream& o) const throw ()
  {
    o << file_ << ':' << line_ << ": " << message_;
    return o;
  }


  std::ostream&
  operator<< (std::ostream& o, const Exception& exception)
  {
    exception.print (o);
    return o;
  }

} // end of namespace hpp.
