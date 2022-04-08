// Copyright (C) 2010 by Thomas Moulard, CNRS.
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

#include "hpp/util/timer.hh"

#include <iomanip>
#include <iostream>

using namespace std::chrono;

namespace hpp {
namespace debug {
Timer::Timer(bool autoStart) : start_(), end_() {
  if (autoStart) start();
}

Timer::Timer(const Timer& timer) : start_(timer.start_), end_(timer.end_) {}

Timer& Timer::operator=(const Timer& timer) {
  if (this == &timer) return *this;
  start_ = timer.start_;
  end_ = timer.end_;
  return *this;
}

Timer::~Timer() {}

const Timer::time_point& Timer::start() { return start_ = clock_type::now(); }

const Timer::time_point& Timer::stop() { return end_ = clock_type::now(); }

const Timer::time_point& Timer::getStart() const { return start_; }

const Timer::time_point& Timer::getStop() const { return end_; }

double Timer::duration() const { return duration_type(end_ - start_).count(); }

std::ostream& Timer::print(std::ostream& o) const {
  auto time = clock_type::to_time_t(start_);
  return o << "timer started at "
           << std::put_time(std::localtime(&time), "%F %T")
           << " and elapsed time "
              "is "
           << duration();
}

TimeCounter::TimeCounter(const std::string& name)
    : n_(name),
      c_(0),
      t_(duration_type::zero()),
      min_(duration_type::max()),
      max_(duration_type::min()) {}

void TimeCounter::start() { s_ = clock_type::now(); }

double TimeCounter::stop() {
  last_ = clock_type::now() - s_;
  min_ = std::min(last_, min_);
  max_ = std::max(last_, max_);
  t_ += last_;
  ++c_;
  return last_.count();
}

double TimeCounter::last() { return last_.count(); }

void TimeCounter::reset() {
  t_ = duration_type::zero();
  c_ = 0;
  min_ = duration_type::max();
  max_ = duration_type::min();
}

double TimeCounter::min() const { return min_.count(); }

double TimeCounter::max() const { return max_.count(); }

double TimeCounter::mean() const {
  return (c_ > 0) ? (t_ / (int)c_).count() : 0;
}

double TimeCounter::totalTime() const { return t_.count(); }

std::ostream& TimeCounter::print(std::ostream& os) const {
  return os << "Time Counter " << n_ << ": " << c_ << ", " << totalTime()
            << ", [ " << min() << ", " << mean() << ", " << max() << "]";
}

std::ostream& operator<<(std::ostream& os, const TimeCounter& tc) {
  return tc.print(os);
}
}  // end of namespace debug
}  // end of namespace hpp
