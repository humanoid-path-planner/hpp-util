# Copyright (C) 2010, 2020 Florent Lamiraux, Thomas Moulard, Guilhem Saurel, JRL, CNRS/AIST, LAAS-CNRS
#

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
# DAMAGE.

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(PROJECT_NAME hpp-util)
SET(PROJECT_DESCRIPTION "Debugging tools for the HPP project.")
SET(PROJECT_URL "http://github.com/humanoid-path-planner/hpp-util")

INCLUDE(cmake/hpp.cmake)
INCLUDE(cmake/boost.cmake)

SET(CXX_DISABLE_WERROR 1)
SET(PROJECT_USE_CMAKE_EXPORT TRUE)

COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX C)
PROJECT(${PROJECT_NAME} ${PROJECT_ARGS})
CHECK_MINIMAL_CXX_STANDARD(14 REQUIRED)

# Search for Boost.
ADD_PROJECT_DEPENDENCY(Boost REQUIRED COMPONENTS filesystem serialization)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/find-external/TinyXML)
FIND_PACKAGE(TinyXML REQUIRED)

SET(${PROJECT_NAME}_HEADERS
  include/hpp/util/assertion.hh
  include/hpp/util/debug.hh
  include/hpp/util/doc.hh
  include/hpp/util/exception.hh
  include/hpp/util/exception-factory.hh
  include/hpp/util/indent.hh
  include/hpp/util/pointer.hh
  include/hpp/util/timer.hh
  include/hpp/util/version.hh
  include/hpp/util/parser.hh
  include/hpp/util/factories/ignoretag.hh
  include/hpp/util/factories/sequence.hh
  include/hpp/util/serialization.hh
  include/hpp/util/serialization-fwd.hh
  include/hpp/util/string.hh
  )

SET(${PROJECT_NAME}_SOURCES
  src/debug.cc
  src/exception.cc
  src/indent.cc
  src/timer.cc
  src/version.cc
  src/parser.cc
  src/factories/sequence.cc
  )

ADD_LIBRARY(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${TinyXML_INCLUDE_DIR})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include>)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${TinyXML_LIBRARY} Boost::filesystem Boost::serialization)

# Check for unistd.h presence.
INCLUDE(CheckIncludeFiles)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)
IF(${HAVE_UNISTD_H})
  TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE -DHAVE_UNISTD_H)
ENDIF(${HAVE_UNISTD_H})

# Define logging directory location.
TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE -DHPP_LOGGINGDIR="${CMAKE_INSTALL_PREFIX}/var/log")

# Set shared library version.
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})

INSTALL(TARGETS ${PROJECT_NAME} EXPORT ${TARGETS_EXPORT_NAME} DESTINATION lib)

ADD_SUBDIRECTORY(tests)

PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})
INSTALL(FILES package.xml DESTINATION share/${PROJECT_NAME})
