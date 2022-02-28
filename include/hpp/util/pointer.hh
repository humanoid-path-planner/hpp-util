// Copyright (C) 2013 by Antonio El Khoury, CNRS.
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

#ifndef HPP_UTIL_POINTER_HH
# define HPP_UTIL_POINTER_HH

# include <memory>

namespace hpp {
  using std::shared_ptr;
  using std::weak_ptr;

  using std::static_pointer_cast;
  using std::dynamic_pointer_cast;
  using std::const_pointer_cast;

  using std::make_shared;
} // namespace hpp

/// Defines the four types of smart pointers associated with type <tt>\a t</tt>.
/// If <tt>\a t</tt> is \c CMyClass then
///  - the type of a shared pointer to <tt>\a t</tt> is \c CMyClassShPtr
///  - the type of a weak pointer to <tt>\a t</tt> is \c CMyClassWkPtr_t
///  - the type of a shared pointer to <tt>\a t const</tt> is
///    \c CMyClassConstShPtr
///  - the type of a weak pointer to <tt>\a t const</tt> is
///    \c CMyClassConstWkPtr_t

# define HPP_POINTER_DEFS(t)		 \
  typedef hpp::weak_ptr <t> t##WkPtr_t;		 \
  typedef hpp::weak_ptr <const t> t##ConstWkPtr_t;	 \
  struct e_n_d__w_i_t_h__s_e_m_i_c_o_l_o_n

/** Makes a forward declaration of class <tt>\a t</tt> and of the four
*   types of shared pointers associated with it.
*/
# define HPP_PREDEF_CLASS(t)		\
  class t;					\
  HPP_POINTER_DEFS(t);			\
  struct e_n_d__w_i_t_h__s_e_m_i_c_o_l_o_n

# define HPP_STATIC_PTR_CAST(t, x) hpp::static_pointer_cast < t > (x)
# define HPP_DYNAMIC_PTR_CAST(t, x) hpp::dynamic_pointer_cast < t > (x)
# ifndef NDEBUG
#  define HPP_STATIC_CAST_REF_CHECK(t, x)\
  try {\
    dynamic_cast < t& > (x);\
  } catch (const std::exception& exc) {\
      assert ("Cast in #t failed" && 0);\
  }
# else
#  define HPP_STATIC_CAST_REF_CHECK(t, x)
# endif // defined NDEBUG
#endif //! HPP_UTIL_POINTER_HH
