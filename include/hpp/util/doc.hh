// Copyright 2010, Thomas Moulard, CNRS/AIST
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

/**
   \mainpage

   The hpp-util library gathers technical tools for the HPP project.

   This package does not target specifically path planning or robotics.

   It provides:
   - logging mechanisms (different channels are linked to several outputs).
   - benchmark tools
   - quality assurance tools (contract programming tools
     and "smart" assertions).
   - \ref hpp_util_serialization "tools for serialization" used in HPP.

   The Doxygen documentation has been written to be a reference document.
   For tutorials and more user-friendly documentation, see the
   <a href="http://github.com/laas/hpp-util/wiki">hpp-util wiki</a>.

   Bug reporting can be done through the
   <a href="http://github.com/laas/hpp-util/issues">github ticketing
   system</a>.

   \defgroup hpp_util_debugging Macros for debugging

   \defgroup hpp_util_logging Macros for logging

   \defgroup hpp_util_exceptions Macros for \c std::exception

   It eases throwing exceptions built from string stream. You can use equivalently
   \code
     HPP_THROW(std::runtime_error, "message" << variable);
   \endcode
   or
   \code
     HPP_THROW_WITH_LINEINFO(std::runtime_error, "message" << variable);
   \endcode
   or
   \code
     throw ::hpp::ExceptionFactory<std::runtime_error>() << "message" << variable << ::hpp::ThrowException();
   \endcode

   \page hpp_util_serialization Serialization

   Serialization of a class hierarchy can be done as follows. The class hierarchy is:
   - AB inherits from A
   - ABC inherits from AB (which inherits from A), thus there cannot be at the same time ABC and DBC.

   In the header file,
   - Use one of the \ref HPP_SERIALIZABLE macros.
   - Except for the base class of the hierarchy (that is A), call \c BOOST_CLASS_EXPORT_KEY(AB)

   In the definition file,
   - implement a function like
     \code
       template<class Archive>
       void AB::serialize(Archive & ar, const unsigned int version)
       {
         using namespace boost::serialization;
         (void) version;
         ar & make_nvp("base", base_object<A>(*this)); // declare inheritance.
         // ...
       }

       HPP_SERIALIZATION_IMPLEMENT(AB); // Or the implement macro corresponding the called declaration macro.
     \endcode
   - Except for the base class of the hierarchy (that is A), call \c BOOST_CLASS_EXPORT_IMPLEMENT(AB)

   If you know a class will not have any serializable child (i.e. AB exists but there is no no ABC), then
   you can remove \c BOOST_CLASS_EXPORT_KEY(AB) and replace \c BOOST_CLASS_EXPORT_IMPLEMENT(AB) by \c BOOST_CLASS_EXPORT(AB)
*/
