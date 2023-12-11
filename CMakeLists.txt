# Copyright (C) 2010, 2020 Florent Lamiraux, Thomas Moulard, Guilhem Saurel,
# JRL, CNRS/AIST, LAAS-CNRS
#

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# 1. Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME hpp-util)
set(PROJECT_DESCRIPTION "Debugging tools for the HPP project.")
set(PROJECT_URL "http://github.com/humanoid-path-planner/hpp-util")

include(cmake/hpp.cmake)
include(cmake/boost.cmake)

set(CXX_DISABLE_WERROR 1)
set(PROJECT_USE_CMAKE_EXPORT TRUE)

compute_project_args(PROJECT_ARGS LANGUAGES CXX C)
project(${PROJECT_NAME} ${PROJECT_ARGS})
check_minimal_cxx_standard(14 REQUIRED)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/find-external/TinyXML)

add_project_dependency(Boost REQUIRED COMPONENTS filesystem serialization)
add_project_dependency(TinyXML2 REQUIRED FIND_EXTERNAL TinyXML)

set(${PROJECT_NAME}_HEADERS
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
    include/hpp/util/string.hh)

set(${PROJECT_NAME}_SOURCES
    src/debug.cc
    src/exception.cc
    src/indent.cc
    src/timer.cc
    src/version.cc
    src/parser.cc
    src/factories/sequence.cc)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES}
                                   ${${PROJECT_NAME}_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(
  ${PROJECT_NAME} PUBLIC tinyxml2::tinyxml2 Boost::filesystem
                         Boost::serialization)

# Check for unistd.h presence.
include(CheckIncludeFiles)
check_include_files(unistd.h HAVE_UNISTD_H)
if(${HAVE_UNISTD_H})
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DHAVE_UNISTD_H)
endif(${HAVE_UNISTD_H})

# Define logging directory location.
target_compile_definitions(
  ${PROJECT_NAME} PRIVATE -DHPP_LOGGINGDIR="${CMAKE_INSTALL_PREFIX}/var/log")

# Set shared library version.
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION lib)

add_subdirectory(tests)

pkg_config_append_libs(${PROJECT_NAME})
install(FILES package.xml DESTINATION share/${PROJECT_NAME})
