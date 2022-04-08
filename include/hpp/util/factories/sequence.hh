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

#ifndef HPP_UTIL_FACTORIES_SEQUENCE_HH
#define HPP_UTIL_FACTORIES_SEQUENCE_HH

#include <vector>

#include "hpp/util/parser.hh"

namespace hpp {
namespace util {
namespace parser {
/// \addtogroup factories
/// \{

/// \brief  Factory parsing sequence of values.
/// \tparam ValueType one of (bool, int, unsigned int, double, float)
///
/// A std::vector is built from a sequence of values separeted by
/// white spaces.
template <typename ValueType>
class SequenceFactory : public ObjectFactory {
 public:
  typedef std::vector<ValueType> OutType;
  SequenceFactory(ObjectFactory* parent, const XMLElement* element,
                  const unsigned int nbValue = 0)
      : ObjectFactory(parent, element), size_(nbValue) {}

  virtual void addTextChild(const XMLText* text);

  const OutType& values() const { return values_; }

  SequenceFactory(const std::string& tagName, ObjectFactory* parent = NULL)
      : ObjectFactory(tagName, parent) {}

  void values(const OutType& v) { values_ = v; }

 protected:
  virtual void impl_write(XMLElement* element) const;

 private:
  std::vector<ValueType> values_;
  unsigned int size_;
};

/// \}
}  // namespace parser
}  // namespace util
}  // namespace hpp

#endif  // HPP_UTIL_FACTORIES_SEQUENCE_HH
