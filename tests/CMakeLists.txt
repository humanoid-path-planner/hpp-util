# Copyright (C) 2010 Florent Lamiraux, Thomas Moulard, JRL, CNRS/AIST.
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

# DEFINE_TEST(NAME)
# -----------------
#
# Compile a program and add it as a test.
#
MACRO(DEFINE_TEST NAME)
  ADD_UNIT_TEST(${NAME} ${NAME}.cc)
  TARGET_LINK_LIBRARIES(${NAME} ${PROJECT_NAME})
ENDMACRO(DEFINE_TEST)

# Define tests.
DEFINE_TEST(simple-test)
DEFINE_TEST(assertion)
DEFINE_TEST(exception)
DEFINE_TEST(exception-factory)
DEFINE_TEST(timer)
DEFINE_TEST(string)

ADD_UNIT_TEST(serialization serialization.cc serialization-test.cc)
TARGET_LINK_LIBRARIES(serialization ${PROJECT_NAME})

SET(HPP_LOGGINGDIR "${CMAKE_CURRENT_BINARY_DIR}")
CONFIG_FILES(run_debug.sh)
ADD_EXECUTABLE(debug debug.cc)
TARGET_LINK_LIBRARIES(debug ${PROJECT_NAME})
ADD_TEST(NAME debug COMMAND ${RUNTIME_OUTPUT_DIRECTORY}/run_debug.sh)
