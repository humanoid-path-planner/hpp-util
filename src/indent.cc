// Copyright (C) 2009, 2010 by Thomas Moulard, CNRS.
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
#include <iomanip>
#include <ostream>

#include "hpp/util/indent.hh"

namespace hpp
{
  inline long& indent (std::ostream& o)
  {
    // The slot to store the current indentation level.
    static const int indent_index = std::ios::xalloc ();
    return o.iword (indent_index);
  }

  std::ostream& incindent (std::ostream& o)
  {
    indent (o) += 2;
    return o;
  }

  std::ostream& decindent (std::ostream& o)
  {
    long& ind = indent(o);
    if (ind >= 2)
      indent (o) -= 2;
    else ind = 0;
    return o;
  }

  std::ostream& resetindent (std::ostream& o)
  {
    indent (o) = 0;
    return o;
  }

  std::ostream& iendl (std::ostream& o)
  {
    o << std::endl;
    // Be sure to be able to restore the stream flags.
    char fill = o.fill (' ');
    return o << std::setw ((int)indent (o))
	     << ""
	     << std::setfill (fill);
  }

  std::ostream& incendl (std::ostream& o)
  {
    return o << incindent << iendl;
  }

  std::ostream& decendl (std::ostream& o)
  {
    return o << decindent << iendl;
  }

} // end of namespace hpp.
