// Copyright (c) 2014, LAAS-CNRS
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-manipulation-urdf.
// hpp-manipulation-urdf is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-manipulation-urdf is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-manipulation-urdf. If not, see <http://www.gnu.org/licenses/>.

#include "hpp/util/factories/sequence.hh"

#include <hpp/util/string.hh>
#include <iostream>

#include "hpp/util/debug.hh"

namespace hpp {
  namespace util {
    namespace parser {
      namespace {
        struct StringIsEmpty : public std::unary_function<std::string, bool>{
          bool operator () (std::string s) const {return s.empty ();}
        };

        template <typename ValueType> bool cast (const std::string& str, ValueType* val)
        {
          hppDout (error, "Unkown type.");
          return false;
        }

        template <> bool cast <int> (const std::string& str, int* val)
        {
          if ( TIXML_SSCANF (str.c_str (), "%d", val) == 1 )
            return true;
          *val = 0;
          return false;
        }

        template <> bool cast <unsigned int> (const std::string& str, unsigned int* val)
        {
          if ( TIXML_SSCANF (str.c_str (), "%u", val) == 1 )
            return true;
          *val = 0;
          return false;
        }

        template <> bool cast <double> (const std::string& str, double* val)
        {
          if ( TIXML_SSCANF (str.c_str (), "%lf", val) == 1 )
            return true;
          *val = 0;
          return false;
        }

        template <> bool cast <float> (const std::string& str, float* val)
        {
          if ( TIXML_SSCANF (str.c_str (), "%f", val) == 1 )
            return true;
          *val = 0;
          return false;
        }

        template <> bool cast <bool> (const std::string& str, bool* val)
        {
          int iVal;
          if (cast <int> (str, &iVal)) {
            *val = (iVal == 0) ? false : true;
            return true;
          }
          if (str.compare ("true") == 0) {
            *val = true;
            return true;
          }
          if (str.compare ("false") == 0) {
            *val = false;
            return true;
          }
          *val = 0;
          return false;
        }

        template <> bool cast <std::string> (const std::string& str, std::string* val)
        {
          *val = str;
          return true;
        }
      }

      template <typename ValueType>
      void SequenceFactory<ValueType>::addTextChild (const XMLText* text)
      {
        values_.clear ();
        std::string t(text->Value ());
        typedef std::vector<std::string> strings_t;
        strings_t values = string_split(t.begin(), t.end(), " \n\t\r");
        auto end = std::remove(values.begin(), values.end(), std::string());
        values.erase(end, values.end());
        if (size_ > 0 && values.size () != size_)
          throw std::invalid_argument ("Wrong sequence size");

        ValueType v;
        for (const std::string s : values) {
          if (!cast <ValueType> (s, &v)) {
            hppDout (error, "could not parse value "<< s);
          }
          values_.push_back (v);
        }
      }

      template <typename ValueType>
      void SequenceFactory<ValueType>::impl_write (XMLElement* element) const
      {
        std::stringstream ss;
        for (typename OutType::const_iterator it = values_.begin ();
            it != values_.end (); ++it) {
          ss << *it << " ";
        }
        element->InsertEndChild (XMLText (ss.str()));
      }

      template class SequenceFactory <bool>;
      template class SequenceFactory <int>;
      template class SequenceFactory <unsigned int>;
      template class SequenceFactory <double>;
      template class SequenceFactory <float>;
      template class SequenceFactory <std::string>;
    } // namespace parser
  } // namespace manipulation
} // namespace hpp
