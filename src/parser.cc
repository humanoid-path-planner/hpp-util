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

#include "hpp/util/parser.hh"

#include <stdexcept>

#include "hpp/util/debug.hh"

namespace hpp {
namespace util {
namespace parser {
Parser::Parser(FactoryType defaultFactory)
    : doc_(), root_(NULL), defaultFactory_(defaultFactory) {}

Parser::~Parser() {
  for (ObjectFactoryList::iterator it = objectFactories_.begin();
       it != objectFactories_.end(); ++it)
    delete *it;
  if (root_ != NULL) delete root_;
}

void Parser::parse(const char* xmlString) {
  doc_.Parse(xmlString);

  parse();
}

void Parser::parseFile(const std::string& filename) {
  doc_.LoadFile(filename.c_str());
  parse();
}

bool Parser::checkError() const {
  if (doc_.Error()) {
    hppDout(error, doc_.ErrorStr());
    return true;
  }
  return false;
}

void Parser::parse() {
  const XMLElement* el = doc_.RootElement();
  root_ = new ObjectFactory();
  while (el != NULL) {
    parseElement(el, root_);
    el = el->NextSiblingElement();
  }
  for (ObjectFactoryList::iterator it = objectFactories_.begin();
       it != objectFactories_.end(); ++it)
    (*it)->finishFile();
}

void Parser::addObjectFactory(const std::string& tagname, FactoryType factory) {
  ObjectFactoryInsertRet ret =
      objFactoryMap_.insert(ObjectFactoryPair(tagname, factory));
  if (!ret.second) throw std::logic_error("This tagname already exist");
}

void Parser::parseElement(const XMLElement* element, ObjectFactory* parent) {
  if (element == NULL) return;

  ObjectFactory* o = NULL;
  /// Look for this element in the map
  ObjectFactoryMap::const_iterator it = objFactoryMap_.find(element->Value());
  if (it != objFactoryMap_.end())
    o = it->second(parent, element);
  else {
    o = defaultFactory_(parent, element);
    hppDout(warning, "I have no factory for tag " << o->tagName());
  }
  objectFactories_.push_back(o);
  if (!o->init()) return;
  for (const XMLAttribute* attr = element->FirstAttribute(); attr;
       attr = attr->Next())
    o->setAttribute(attr);
  if (!o->finishAttributes()) return;

  /// Loop over is child tags
  for (const XMLNode* el = element->FirstChild(); el; el = el->NextSibling()) {
    if (el->ToElement() != NULL) {
      parseElement(el->ToElement(), o);
    } else if (el->ToUnknown() != NULL) {
      hppDout(warning, "Unknown Node in XML file: " << el->Value());
    } else if (el->ToText() != NULL) {
      o->addTextChild(el->ToText());
    } else if (el->ToComment() != NULL) {
    }
  }
  o->finishTags();
}

ObjectFactory* Parser::root() const { return root_; }

std::ostream& Parser::print(std::ostream& os) const {
  os << "Parser with " << objectFactories_.size() << " object." << std::endl;
  if (root_ != NULL) os << *root_;
  return os;
}

std::ostream& operator<<(std::ostream& os, const Parser& p) {
  return p.print(os);
}

std::ostream& operator<<(std::ostream& os, const ObjectFactory& o) {
  return o.print(os);
}

ObjectFactory::ObjectFactory(ObjectFactory* parent, const XMLElement* element)
    : parent_(parent), root_(NULL), element_(element), id_(-1) {
  if (element_ != NULL)
    tagName_ = element_->Value();
  else
    tagName_ = "unamed_tag";
  if (parent_ == NULL) {
    root_ = this;
  } else {
    root_ = parent_->root();
    if (element_ != NULL) parent_->addChild(this);
  }
}

ObjectFactory::ObjectFactory(ObjectFactory* root)
    : parent_(NULL), root_(root), element_(NULL), id_(-1) {}

bool ObjectFactory::init() { return true; }

bool ObjectFactory::finishAttributes() { return true; }

void ObjectFactory::finishTags() {}

void ObjectFactory::finishFile() {}

void ObjectFactory::addTextChild(const XMLText* /* text */) {}

ObjectFactory::ObjectFactory(const std::string& tagName, ObjectFactory* parent)
    : parent_(parent), root_(NULL), element_(NULL), tagName_(tagName), id_(-1) {
  if (parent_ == NULL)
    root_ = this;
  else {
    root_ = parent_->root();
    parent_->addChild(this);
  }
}

void ObjectFactory::addAttribute(const std::string& name,
                                 const std::string& value) {
  attrMap_[name] = value;
}

/// Get a new XMLElement from the content of this factory
XMLNode* ObjectFactory::write(XMLNode* parent) const {
  XMLElement* el = parent->GetDocument()->NewElement(tagName().c_str());
  for (AttributeMap::const_iterator it = attrMap_.begin(); it != attrMap_.end();
       ++it)
    el->SetAttribute(it->first.c_str(), it->second.c_str());
  for (ChildrenMap::const_iterator it = children_.begin();
       it != children_.end(); ++it)
    for (ObjectFactoryList::const_iterator of = it->second.begin();
         of != it->second.end(); ++of)
      (*of)->write(el);
  impl_write(el);
  return parent->InsertEndChild(el);
}

std::string ObjectFactory::tagName() const { return tagName_; }

std::string ObjectFactory::name() const { return name_; }

void ObjectFactory::name(const std::string& n) { name_ = n; }

void ObjectFactory::name(const char* n) { name(std::string(n)); }

ObjectFactory* ObjectFactory::parent() { return parent_; }

ObjectFactory* ObjectFactory::root() { return root_; }

bool ObjectFactory::hasParent() const { return parent_ != NULL; }

const XMLElement* ObjectFactory::XMLelement() { return element_; }

void ObjectFactory::impl_setAttribute(const XMLAttribute* /* attr */) {}

void ObjectFactory::impl_write(XMLElement*) const {}

void ObjectFactory::addChild(ObjectFactory* child) {
  children_[child->tagName()].push_back(child);
}

std::list<ObjectFactory*> ObjectFactory::getChildrenOfType(std::string type) {
  return children_[type];
}

bool ObjectFactory::getChildOfType(std::string type, ObjectFactory*& o) {
  ObjectFactoryList l = getChildrenOfType(type);
  if (l.empty()) {
    throw std::invalid_argument("Tag " + tagName() + " has no child of type " +
                                type);
  }
  o = l.front();
  if (l.size() != 1) {
    hppDout(warning, "Tag " << tagName() << " has several children of type "
                            << type << ". All but the first will be ignored.");
    return false;
  }
  return true;
}

std::ostream& ObjectFactory::print(std::ostream& os) const {
  os << "ObjectFactory " << tagName() << " with name " << name() << std::endl;
  for (ChildrenMap::const_iterator itTagName = children_.begin();
       itTagName != children_.end(); ++itTagName)
    for (ObjectFactoryList::const_iterator itObj = itTagName->second.begin();
         itObj != itTagName->second.end(); ++itObj)
      os << **itObj;
  return os;
}

void ObjectFactory::setAttribute(const XMLAttribute* attr) {
  std::string n = std::string(attr->Name());
  if (n == "name")
    name(attr->Value());
  else if (n == "id") {
    int v;
    if (attr->QueryIntValue(&v) != tinyxml2::XML_SUCCESS) {
      hppDout(error, "Attribute ID " << attr->Value() << " is incorrect.");
    } else {
      id_ = (int)v;
    }
  }
  attrMap_[n] = attr->Value();
  impl_setAttribute(attr);
}

bool ObjectFactory::hasAttribute(const std::string& attr) const {
  return attrMap_.find(attr) != attrMap_.end();
}

std::string ObjectFactory::getAttribute(const std::string& attr) const {
  AttributeMap::const_iterator it = attrMap_.find(attr);
  if (it == attrMap_.end()) {
    hppDout(error, "Asking for attribute " << attr);
    return std::string();
  }
  return it->second;
}
}  // namespace parser
}  // namespace util
}  // namespace hpp
