# Copyright (C) 2010 Florent Lamiraux, Thomas Moulard, JRL, CNRS/AIST.
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

# DEFINE_TEST(NAME)
# -----------------
#
# Compile a program and add it as a test.
#
macro(DEFINE_TEST NAME)
  add_unit_test(${NAME} ${NAME}.cc)
  target_include_directories(${NAME} PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(${NAME} ${PROJECT_NAME})
endmacro(DEFINE_TEST)

# Define tests.
define_test(simple-test)
define_test(assertion)
define_test(exception)
define_test(exception-factory)
define_test(timer)
define_test(string)

add_unit_test(serialization serialization.cc serialization-test.cc)
target_link_libraries(serialization ${PROJECT_NAME})

set(HPP_LOGGINGDIR "${CMAKE_CURRENT_BINARY_DIR}")
config_files(run_debug.sh)
add_executable(debug debug.cc)
target_include_directories(debug PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(debug ${PROJECT_NAME})
add_test(NAME debug COMMAND ${RUNTIME_OUTPUT_DIRECTORY}/run_debug.sh)
