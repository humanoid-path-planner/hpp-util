//
// Copyright (c) 2020 CNRS
// Authors: Joseph Mirabel
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

#ifndef HPP_UTIL_SERIALIZATION_HH
#define HPP_UTIL_SERIALIZATION_HH

#include <boost/version.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>

#include <hpp/util/config.hh>
#include <hpp/util/serialization-fwd.hh>

#define _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type,archive,arg)                   \
  template void type load<archive##_iarchive>(archive##_iarchive& ar,          \
      arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg)))              \
      const unsigned int ver);                                                 \
  template void type save<archive##_oarchive>(archive##_oarchive& ar,          \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(arg),,const) arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg))) \
    const unsigned int ver) BOOST_PP_IF(BOOST_PP_IS_EMPTY(arg),const,)

#define _HPP_SERIALIZATION_IMPLEMENT(type,archive,arg)                         \
    template void type serialize<archive##_iarchive>(archive##_iarchive& ar,   \
        arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg)))            \
        const unsigned int ver);                                               \
    template void type serialize<archive##_oarchive>(archive##_oarchive& ar,   \
        arg BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(arg)))            \
        const unsigned int ver)

#define HPP_SERIALIZATION_SPLIT_IMPLEMENT(type)                                \
    _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type::,boost::archive::xml,);           \
    _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type::,boost::archive::text,);          \
    _HPP_SERIALIZATION_SPLIT_IMPLEMENT(type::,boost::archive::binary,)

#define HPP_SERIALIZATION_IMPLEMENT(type)                                      \
    _HPP_SERIALIZATION_IMPLEMENT(type::,boost::archive::xml,);                 \
    _HPP_SERIALIZATION_IMPLEMENT(type::,boost::archive::text,);                \
    _HPP_SERIALIZATION_IMPLEMENT(type::,boost::archive::binary,)

#define HPP_SERIALIZATION_FREE_IMPLEMENT(type)                                 \
    namespace boost { namespace serialization {                                \
    _HPP_SERIALIZATION_IMPLEMENT(,archive::xml,type& t);                       \
    _HPP_SERIALIZATION_IMPLEMENT(,archive::text,type& t);                      \
    _HPP_SERIALIZATION_IMPLEMENT(,archive::binary,type& t);                    \
    }}

#define HPP_SERIALIZATION_SPLIT_FREE_IMPLEMENT(type)                           \
  namespace boost { namespace serialization {                                  \
  template<class Archive>                                                      \
  void serialize(Archive & ar, type& t, const unsigned int version) {          \
    split_free(ar, t, version);                                                \
  }                                                                            \
  _HPP_SERIALIZATION_IMPLEMENT(,archive::xml,type& t);                         \
  _HPP_SERIALIZATION_IMPLEMENT(,archive::text,type& t);                        \
  _HPP_SERIALIZATION_IMPLEMENT(,archive::binary,type& t);                      \
  }}

namespace hpp {
namespace serialization {
using boost::serialization::make_nvp;
using boost::serialization::guid;
using boost::serialization::guid_defined;

class holder_base {
public:
  const char* classid;
  virtual ~holder_base() = default;

protected:
  holder_base(const char* classid) : classid(classid) {}
};

template<typename T> class holder : public holder_base {
public:
  T* t;
  holder(T* t, const char* classid) : holder_base(classid), t(t) {}
  holder(T* t) : holder(t, guid<T>())
  { static_assert(guid_defined<T>::value, "You must use BOOST_CLASS_EXPORT_KEY on this class first."); }

  template <typename U> explicit operator holder<U>() { return holder<U>(dynamic_cast<U*>(t), classid); }
};

class archive_ptr_holder
{
  std::map<std::string, holder_base*> ptrs_;

public:
  bool contains(const std::string& k) const { return ptrs_.count(k); }
  template<typename T>
  bool containsOfType(const std::string& k) const { return (get<T>(k, false)) != NULL; }

  void insert(const std::string& k, holder_base* ptr) { ptrs_[k] = ptr; }
  template<typename T>
  void insert(const std::string& k, T* ptr) { insert(k, (holder_base*)new holder<T>(ptr)); }
  holder_base* get(const std::string& k, bool throwIfNotFound = false) const {
    auto _ptr = ptrs_.find(k);
    if (_ptr == ptrs_.end()) {
      if (!throwIfNotFound) return NULL;
      throw std::invalid_argument("Pointer with name " + k + " not found.");
    }
    else return _ptr->second;
  }
  template<typename T>
  T* get(const std::string& k, bool throwIfNotFound = false) const {
    holder_base* hb (get(k, throwIfNotFound));
    if (hb == NULL) return NULL;
    holder<T>* h;
    if ((h = dynamic_cast<holder<T>*>(hb)) == NULL) {
      if (!throwIfNotFound) return NULL;
      throw std::invalid_argument("Pointer with name " + k + " found of type "
          + hb->classid + " but not of requested type " + guid<T>() + ".");
    }
    return h->t;
  }

  template<typename Base, typename Child>
  void insertChildClass(const std::string& k, Child* ptr) {
    static_assert(guid_defined<Child>::value, "You must use BOOST_CLASS_EXPORT_KEY on this class first.");
    insert(k, (holder_base*)new holder<Base>(ptr, guid<Child>()));
  }
  template<typename Base, typename Child>
  Child* getChildClass(const std::string& k, bool throwIfNotFound = false) const {
    holder_base* hb (get(k, throwIfNotFound));
    if (hb == NULL) return NULL;
    holder<Base>* b;
    if ((b = dynamic_cast<holder<Base>*>(hb)) == NULL) {
      if (!throwIfNotFound) return NULL;
      throw std::invalid_argument("Pointer with name " + k + " found of type "
          + hb->classid + " but not of requested type " + guid<Child>() + ".");
    }
    holder<Child> c (*b);
    if (c.t == NULL) {
      if (!throwIfNotFound) return NULL;
      throw std::invalid_argument("Pointer with name " + k + " found of type "
          + hb->classid + " but not of requested type " + guid<Child>() + ".");
    }
    return c.t;
  }

  virtual ~archive_ptr_holder() {
    for (auto it : ptrs_) delete it.second;
  }

protected:
  template<typename Archive, std::enable_if_t<Archive::is_saving::value, int> = 42>
  void initialize_tpl(Archive& ar) // save
  {
    auto size (ptrs_.size());
    ar << make_nvp("nrequires", size);
    typedef std::pair<std::string,std::string> string_pair;
    for (auto it : ptrs_) {
      string_pair requires(it.first, it.second->classid);
      ar << make_nvp("requires", requires);
    }
  }
  template<typename Archive, std::enable_if_t<!Archive::is_saving::value, int> = 42>
  void initialize_tpl(Archive& ar) // read
  {
    decltype(ptrs_.size()) size;
    ar >> make_nvp("nrequires", size);
    typedef std::pair<std::string,std::string> string_pair;
    string_pair pair;
    for (decltype(size) i = 0; i < size; ++i) {
      ar >> make_nvp("requires", pair);
      holder_base* hb = get(pair.first, true);
      if (pair.second != hb->classid)
        throw std::invalid_argument("Required pointer with name " + pair.first + " found of type "
            + hb->classid + " but not of required type " + pair.second + ".");
    }
  }
};

template<typename archive_base, typename... parent_classes>
class archive_tpl : public archive_base, public archive_ptr_holder, public parent_classes...
{
public:
  inline void initialize()
  {
    initialize_tpl<archive_base>(*this);
  }

  using archive_base::archive_base;
};

template<typename Archive>
archive_ptr_holder& cast(Archive& ar) { return dynamic_cast<archive_ptr_holder&>(ar); }
template<typename Archive>
archive_ptr_holder* cast(Archive* ar) { return dynamic_cast<archive_ptr_holder*>(ar); }

typedef archive_tpl<boost::archive::binary_iarchive> binary_iarchive;
typedef archive_tpl<boost::archive::binary_oarchive> binary_oarchive;

typedef archive_tpl<boost::archive::xml_iarchive> xml_iarchive;
typedef archive_tpl<boost::archive::xml_oarchive> xml_oarchive;

typedef archive_tpl<boost::archive::text_iarchive> text_iarchive;
typedef archive_tpl<boost::archive::text_oarchive> text_oarchive;
} // namespace util
} // namespace hpp

#endif // HPP_UTIL_SERIALIZATION_HH
