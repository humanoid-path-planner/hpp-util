// Copyright (c) 2014, LAAS-CNRS
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
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

#include "hpp/util/factories/sequence.hh"

#include <hpp/util/string.hh>
#include <iostream>

#include "hpp/util/debug.hh"

namespace hpp {
namespace util {
namespace parser {
namespace {

// copy/paste from tinyxml2.cpp
#if defined(_MSC_VER) && (_MSC_VER >= 1400) && (!defined WINCE)
#define TIXML_SSCANF sscanf_s
#else
#define TIXML_SSCANF sscanf
#endif

struct StringIsEmpty : public std::unary_function<std::string, bool> {
  bool operator()(std::string s) const { return s.empty(); }
};

template <typename ValueType>
bool cast(const std::string& str, ValueType* val) {
  hppDout(error, "Unkown type.");
  return false;
}

template <>
bool cast<int>(const std::string& str, int* val) {
  if (TIXML_SSCANF(str.c_str(), "%d", val) == 1) return true;
  *val = 0;
  return false;
}

template <>
bool cast<unsigned int>(const std::string& str, unsigned int* val) {
  if (TIXML_SSCANF(str.c_str(), "%u", val) == 1) return true;
  *val = 0;
  return false;
}

template <>
bool cast<double>(const std::string& str, double* val) {
  if (TIXML_SSCANF(str.c_str(), "%lf", val) == 1) return true;
  *val = 0;
  return false;
}

template <>
bool cast<float>(const std::string& str, float* val) {
  if (TIXML_SSCANF(str.c_str(), "%f", val) == 1) return true;
  *val = 0;
  return false;
}

template <>
bool cast<bool>(const std::string& str, bool* val) {
  int iVal;
  if (cast<int>(str, &iVal)) {
    *val = (iVal == 0) ? false : true;
    return true;
  }
  if (str.compare("true") == 0) {
    *val = true;
    return true;
  }
  if (str.compare("false") == 0) {
    *val = false;
    return true;
  }
  *val = 0;
  return false;
}

template <>
bool cast<std::string>(const std::string& str, std::string* val) {
  *val = str;
  return true;
}
}  // namespace

template <typename ValueType>
void SequenceFactory<ValueType>::addTextChild(const XMLText* text) {
  values_.clear();
  std::string t(text->Value());
  typedef std::vector<std::string> strings_t;
  strings_t values = string_split(t.begin(), t.end(), " \n\t\r");
  auto end = std::remove(values.begin(), values.end(), std::string());
  values.erase(end, values.end());
  if (size_ > 0 && values.size() != size_)
    throw std::invalid_argument("Wrong sequence size");

  ValueType v;
  for (const std::string s : values) {
    if (!cast<ValueType>(s, &v)) {
      hppDout(error, "could not parse value " << s);
    }
    values_.push_back(v);
  }
}

template <typename ValueType>
void SequenceFactory<ValueType>::impl_write(XMLElement* element) const {
  std::stringstream ss;
  for (typename OutType::const_iterator it = values_.begin();
       it != values_.end(); ++it) {
    ss << *it << " ";
  }
  XMLElement* el = element->GetDocument()->NewElement(ss.str().c_str());
  element->InsertEndChild(el);
}

template class SequenceFactory<bool>;
template class SequenceFactory<int>;
template class SequenceFactory<unsigned int>;
template class SequenceFactory<double>;
template class SequenceFactory<float>;
template class SequenceFactory<std::string>;
}  // namespace parser
}  // namespace util
}  // namespace hpp
