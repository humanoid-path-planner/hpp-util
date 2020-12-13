# Copyright (C) 2010, 2020 Florent Lamiraux, Thomas Moulard, Guilhem Saurel, JRL, CNRS/AIST, LAAS-CNRS
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
  include/hpp/util/portability.hh
  include/hpp/util/timer.hh
  include/hpp/util/version.hh
  include/hpp/util/parser.hh
  include/hpp/util/factories/ignoretag.hh
  include/hpp/util/factories/sequence.hh
  include/hpp/util/serialization.hh
  include/hpp/util/serialization-fwd.hh
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
