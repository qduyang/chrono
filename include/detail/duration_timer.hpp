/****************************************************************************
**
**  Copyright (c) 2018 Du Yang
**
**    Author        : Du Yang <duyang.seu@gmail.com>
**    File          : duration_timer.hpp
**    Date          : 2018/06/06 17:30:00
**    Description   : Duration Timer
**
****************************************************************************/

#ifndef CHRONO_DETAIL_DURATION_TIMER_HPP
#define CHRONO_DETAIL_DURATION_TIMER_HPP

#include <boost/asio/steady_timer.hpp>

#include "basic_timer.hpp"

namespace Chrono::Detail
{
template <class IntervalType = std::chrono::milliseconds,
          class IOExecutor   = boost::asio::io_context,
          class Timer        = boost::asio::steady_timer>
class DurationTimer : public BasicTimer<IntervalType, IOExecutor, Timer,
                                        GetTimeType<Timer>, ExpireAfter>
{
 public:
  using TimePoint = GetTimeType<Timer>;
  using Base =
      BasicTimer<IntervalType, IOExecutor, Timer, TimePoint, ExpireAfter>;

  template <class Interval>
  DurationTimer(IOExecutor& ioe, const Interval& interval, bool recursive)
    : Base{ioe, TimePoint{}, interval, recursive}
  {
  }

  template <class Interval>
  DurationTimer(IOExecutor& ioe, const Interval& interval)
    : DurationTimer{ioe, interval, true}
  {
  }
};

} // namespace Chrono::Detail

#endif
