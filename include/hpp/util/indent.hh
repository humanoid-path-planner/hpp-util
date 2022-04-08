// Copyright (C) 2008, 2009 by Thomas Moulard, CNRS.
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

#ifndef HPP_UTIL_INDENT_HH
#define HPP_UTIL_INDENT_HH
#include <hpp/util/config.hh>
#include <iosfwd>

namespace hpp {
/// \brief The current indentation level for \a o.
HPP_UTIL_DLLAPI long& indent(std::ostream& o);

/// \brief Increment the indentation.
HPP_UTIL_DLLAPI std::ostream& incindent(std::ostream& o);

/// \brief Decrement the indentation.
HPP_UTIL_DLLAPI std::ostream& decindent(std::ostream& o);

/// \brief Reset the indentation.
HPP_UTIL_DLLAPI std::ostream& resetindent(std::ostream& o);

/// \brief Print an end of line, then set the indentation.
HPP_UTIL_DLLAPI std::ostream& iendl(std::ostream& o);

/// \brief Increment the indentation, print an end of line,
/// and set the indentation.
HPP_UTIL_DLLAPI std::ostream& incendl(std::ostream& o);

/// \brief  Decrement the indentation, print an end of line,
/// and set the indentation.
HPP_UTIL_DLLAPI std::ostream& decendl(std::ostream& o);

}  // end of namespace hpp.

#endif  // !HPP_UTIL_INDENT_HH
