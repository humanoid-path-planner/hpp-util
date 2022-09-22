// Copyright (c) 2015, LAAS-CNRS
// Authors: Thomas Moulard, Joseph Mirabel
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

#ifndef HPP_UTIL_TIMER_HH
#define HPP_UTIL_TIMER_HH

#include <chrono>
#include <hpp/util/config.hh>
#include <hpp/util/debug.hh>

namespace hpp {
namespace debug {
class HPP_UTIL_DLLAPI Timer {
 public:
  typedef std::chrono::system_clock clock_type;
  typedef clock_type::time_point time_point;
  typedef std::chrono::duration<double> duration_type;

  explicit Timer(bool autoStart = false);
  Timer(const Timer&);
  Timer& operator=(const Timer&);
  ~Timer();

  const time_point& start();
  const time_point& stop();
  double duration() const;

  const time_point& getStart() const;
  const time_point& getStop() const;

  std::ostream& print(std::ostream&) const;

 private:
  time_point start_;
  time_point end_;
};

#ifdef HPP_ENABLE_BENCHMARK

#define hppStartBenchmark(ID)           \
  hppDout(benchmark, #ID << ": start"); \
  ::hpp::debug::Timer _##ID##_timer_(true)

#define hppStopBenchmark(ID)             \
  do {                                   \
    _##ID##_timer_.stop();               \
    hppDout(benchmark, #ID << ": stop"); \
  } while (0)

#define hppDisplayBenchmark(ID) \
  hppDout(benchmark, #ID << ": " << _##ID##_timer_.duration());

#define hppBenchmark(data)                                                  \
  do {                                                                      \
    using namespace hpp;                                                    \
    using namespace ::hpp::debug;                                           \
    std::stringstream __ss;                                                 \
    __ss << data << iendl;                                                  \
    logging.benchmark.write(__FILE__, __LINE__, __PRETTY_FUNCTION__, __ss); \
  } while (0)

#else
#define hppStartBenchmark(ID)
#define hppStopBenchmark(ID)
#define hppDisplayBenchmark(ID)
#define hppBenchmark(data)
#endif  // HPP_ENABLE_BENCHMARK

/// \brief Computation of min, max and mean time from a set of measurements.
class HPP_UTIL_DLLAPI TimeCounter {
 public:
  struct Scope {
    Scope(TimeCounter& t) : tc(t) { t.start(); }
    ~Scope() { tc.stop(); }

    TimeCounter& tc;
  };

  typedef std::chrono::system_clock clock_type;
  typedef clock_type::time_point time_point;
  typedef std::chrono::duration<double> duration_type;

  TimeCounter(const std::string& name);

  void start();
  double stop();
  double last();
  void reset();

  double min() const;
  double max() const;
  double mean() const;
  double totalTime() const;

  std::ostream& print(std::ostream& os) const;

 private:
  std::string n_;
  unsigned long c_;
  duration_type t_, last_, min_, max_;
  time_point s_;
};

std::ostream& operator<<(std::ostream& os, const TimeCounter& tc);

#ifdef HPP_ENABLE_BENCHMARK

/// \addtogroup hpp_util_logging
/// \{

/// \brief Define a new TimeCounter
#define HPP_DEFINE_TIMECOUNTER(name) \
  ::hpp::debug::TimeCounter _##name##_timecounter_(#name)
/// \brief Compute the time spent in the current scope.
#define HPP_SCOPE_TIMECOUNTER(name)                             \
  ::hpp::debug::TimeCounter::Scope _##name##_scopetimecounter_( \
      _##name##_timecounter_)
/// \brief Start a watch.
#define HPP_START_TIMECOUNTER(name) _##name##_timecounter_.start()
/// \brief Stop a watch and save elapsed time.
#define HPP_STOP_TIMECOUNTER(name) _##name##_timecounter_.stop()
/// \brief Print last elapsed time to the logs.
#define HPP_DISPLAY_LAST_TIMECOUNTER(name)                                  \
  do {                                                                      \
    using namespace hpp;                                                    \
    using namespace ::hpp::debug;                                           \
    std::stringstream __ss;                                                 \
    __ss << #name << " last: " << _##name##_timecounter_.last() << iendl;   \
    logging.benchmark.write(__FILE__, __LINE__, __PRETTY_FUNCTION__, __ss); \
  } while (0)
/// \brief Print min, max and mean time of the time measurements.
#define HPP_DISPLAY_TIMECOUNTER(name)                                       \
  do {                                                                      \
    using namespace hpp;                                                    \
    using namespace ::hpp::debug;                                           \
    std::stringstream __ss;                                                 \
    __ss << _##name##_timecounter_ << iendl;                                \
    logging.benchmark.write(__FILE__, __LINE__, __PRETTY_FUNCTION__, __ss); \
  } while (0)
/// \brief Reset a TimeCounter.
#define HPP_RESET_TIMECOUNTER(name) _##name##_timecounter_.reset();
/// \brief Stream (\c operator<<) to the output stream.
#define HPP_STREAM_TIMECOUNTER(os, name) os << _##name##_timecounter_
/// \}
#else  // HPP_ENABLE_BENCHMARK
#define HPP_DEFINE_TIMECOUNTER(name) \
  struct _##name##_EndWithSemiColon_ {}
#define HPP_SCOPE_TIMECOUNTER(name)
#define HPP_START_TIMECOUNTER(name)
#define HPP_STOP_TIMECOUNTER(name)
#define HPP_DISPLAY_LAST_TIMECOUNTER(name)
#define HPP_DISPLAY_TIMECOUNTER(name)
#define HPP_RESET_TIMECOUNTER(name)
#define HPP_STREAM_TIMECOUNTER(os, name) os
#endif  // HPP_ENABLE_BENCHMARK

#define HPP_STOP_AND_DISPLAY_TIMECOUNTER(name) \
  HPP_STOP_TIMECOUNTER(name);                  \
  HPP_DISPLAY_TIMECOUNTER(name)

}  // end of namespace debug
}  // end of namespace hpp

#endif  // HPP_UTIL_TIMER_HH
