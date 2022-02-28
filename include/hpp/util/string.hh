// Copyright (C) 2020 by Joseph Mirabel, CNRS.
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

#ifndef HPP_UTIL_STRING_HH
# define HPP_UTIL_STRING_HH
# include <hpp/util/config.hh>

#include <vector>
#include <string>
#include <cstring>
#include <iterator>
#include <algorithm>

namespace hpp {
namespace util {

template<typename InputIt, typename Predicate>
bool string_split(InputIt first, InputIt last, const char& c, Predicate p)
{
  while (true) {
    InputIt next = std::find(first, last, c);
    if (p(first, next)) return true;
    if (next == last) return false;
    first = std::next(next);
  }
}

template<typename InputIt, typename Predicate>
bool string_split(InputIt first, InputIt last, const char* c, Predicate p)
{
  auto n = std::strlen(c);
  while (true) {
    InputIt next = std::find_if(first, last,
        [&c, &n](char l)->bool{ return c+n != std::find(c, c+n, l); });
    if (p(first, next)) return true;
    if (next == last) return false;
    first = std::next(next);
  }
}

template<typename InputIt>
std::vector<std::string>
string_split(InputIt first, InputIt last, const char& c)
{
  std::vector<std::string> strings;
  string_split(first, last, c, [&strings](InputIt begin, InputIt end) {
        strings.emplace_back(&(*begin), std::distance(begin, end));
        return false;
      });
  return strings;
}

template<typename InputIt>
std::vector<std::string>
string_split(InputIt first, InputIt last, const char* c)
{
  std::vector<std::string> strings;
  string_split(first, last, c, [&strings](InputIt begin, InputIt end) {
        strings.emplace_back(&(*begin), std::distance(begin, end));
        return false;
      });
  return strings;
}

inline bool iequal(const std::string& a, const std::string& b)
{
  return (a.size() == b.size()) && std::equal(a.begin(), a.end(), b.begin(),
      [](char a, char b)->bool { return std::tolower(a) == std::tolower(b); });
}

} // end of namespace util.
} // end of namespace hpp.

#endif //! HPP_UTIL_STRING_HH
