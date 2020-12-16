// Copyright (C) 2010 by Thomas Moulard, CNRS.
//
// This file is part of the hpp-util.
//
// hpp-util is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// hpp-util is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp-util.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <iomanip>

#include "hpp/util/timer.hh"

using namespace std::chrono;

namespace hpp
{
  namespace debug
  {
    Timer::Timer (bool autoStart)
      : start_ (),
	end_ ()
    {
      if (autoStart)
	start ();
    }

    Timer::Timer (const Timer& timer)
      : start_ (timer.start_),
	end_ (timer.end_)
    {}

    Timer&
    Timer::operator= (const Timer& timer)
    {
      if (this == &timer)
	return *this;
      start_ = timer.start_;
      end_ = timer.end_;
      return *this;
    }

    Timer::~Timer ()
    {}

    const Timer::time_point&
    Timer::start ()
    {
      return start_ = clock_type::now();
    }

    const Timer::time_point&
    Timer::stop ()
    {
      return end_ = clock_type::now();
    }

    const Timer::time_point&
    Timer::getStart () const
    {
      return start_;
    }

    const Timer::time_point&
    Timer::getStop () const
    {
      return end_;
    }

    double
    Timer::duration () const
    {
      return duration_type(end_ - start_).count();
    }

    std::ostream&
    Timer::print (std::ostream& o) const
    {
      auto time = clock_type::to_time_t(start_);
      return o << "timer started at " <<
        std::put_time(std::localtime(&time), "%F %T") << " and elapsed time "
        "is " << duration();
    }

    TimeCounter::TimeCounter (const std::string& name) :
      n_ (name), c_ (0), t_ (duration_type::zero()),
      min_ (duration_type::max()), max_ (duration_type::min())
    {}

    void TimeCounter::start ()
    {
      s_ = clock_type::now();
    }

    double TimeCounter::stop ()
    {
      last_ = clock_type::now() - s_;
      min_ = std::min(last_, min_);
      max_ = std::max(last_, max_);
      t_ += last_;
      ++c_;
      return last_.count();
    }

    double TimeCounter::last ()
    {
      return last_.count();
    }

    void TimeCounter::reset ()
    {
      t_ = duration_type::zero();
      c_ = 0;
      min_ = duration_type::max();
      max_ = duration_type::min();
    }

    double TimeCounter::min () const
    {
      return min_.count();
    }

    double TimeCounter::max () const
    {
      return max_.count();
    }

    double TimeCounter::mean () const
    {
      return ( c_ > 0 ) ? (t_ / (int)c_).count() : 0;
    }

    double TimeCounter::totalTime () const
    {
      return t_.count();
    }

    std::ostream& TimeCounter::print (std::ostream& os) const
    {
      return os << "Time Counter " << n_
        << ": " << c_
        << ", " << totalTime ()
        << ", [ " << min ()
        <<   ", " << mean ()
        <<   ", " << max () << "]"
        ;
    }

    std::ostream& operator<< (std::ostream& os, const TimeCounter& tc)
    {
      return tc.print (os);
    }
  } // end of namespace debug
} // end of namespace hpp
