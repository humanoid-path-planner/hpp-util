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

#include "hpp/util/version.hh"

#include <assert.h>

#include <hpp/util/string.hh>
#include <string>
#include <vector>

#include "config.h"

namespace hpp {
namespace util {
const char* version = PACKAGE_VERSION;

int checkVersion(const char* header_version) {
  std::vector<std::string> headerVersion = string_split(
      header_version, header_version + std::strlen(header_version), '.');
  std::vector<std::string> libraryVersion =
      string_split(version, version + std::strlen(version), '.');

  long unsigned s = std::max(headerVersion.size(), libraryVersion.size());
  headerVersion.resize(s);
  libraryVersion.resize(s);

  assert(headerVersion.size() == libraryVersion.size());

  for (long unsigned i = 0; i < s; ++i)
    if (headerVersion != libraryVersion)
      return (headerVersion > libraryVersion) ? -1 : 1;
  return 0;
}
}  // end of namespace util.
}  // end of namespace hpp.
