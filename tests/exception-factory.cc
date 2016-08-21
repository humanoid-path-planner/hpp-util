// Copyright (C) 2016 by Joseph Mirabel.
//
// This file is part of the hpp-util.
//
// hpp-util is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// hpp-util is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp-util.  If not, see <http://www.gnu.org/licenses/>.

#include <hpp/util/exception-factory.hh>

#include "config.h"

#include <cassert>
#include <stdexcept>
#include <iostream>

#include "common.hh"

int run_test ();

int run_test ()
{
  try
    {
      throw ::hpp::ExceptionFactory<std::runtime_error>() << "manually built std::runtime_error" << ::hpp::ThrowException();
      assert (0);
    }
  catch (const std::exception& exception)
    {
      std::cout << "Caught " << exception.what() << std::endl;
    }

  try
    {
      HPP_THROW(std::runtime_error,"std::runtime_error");
      assert (0);
    }
  catch (const std::exception& exception)
    {
      std::cout << "Caught " << exception.what() << std::endl;
    }

  try
    {
      double d = 12; std::string foo = "foo";
      HPP_THROW_WITH_LINEINFO (std::runtime_error,
          "std::runtime_error using operator<< " << foo << " " << d);
      assert (0);
    }
  catch (const std::exception& exception)
    {
      std::cout << "Caught " << exception.what() << std::endl;
    }
  return 0;
}

GENERATE_TEST ()
