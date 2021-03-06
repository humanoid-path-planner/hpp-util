# Copyright (C) 2010 Florent Lamiraux, Thomas Moulard, JRL, CNRS/AIST.
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
