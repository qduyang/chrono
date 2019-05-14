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

namespace chrono::detail
{
template <
    class IntervalType = std::chrono::milliseconds,
    class IOExecutor   = boost::asio::io_context,
    class Timer        = boost::asio::steady_timer>
class DurationTimer
  : public BasicTimer<
        IntervalType, IOExecutor, Timer, GetTimeType<Timer>, ExpireAfter>
{
 public:
  using TimePoint = GetTimeType<Timer>;
  using Base =
      BasicTimer<IntervalType, IOExecutor, Timer, TimePoint, ExpireAfter>;

  template <class Interval>
  DurationTimer(IOExecutor& ioe, Interval&& interval, bool recursive)
    : Base{ioe, TimePoint{}, std::forward<Interval>(interval), recursive}
  {
  }

  template <class Interval>
  DurationTimer(IOExecutor& ioe, Interval&& interval)
    : DurationTimer{ioe, std::forward<Interval>(interval), true}
  {
  }
};

} // namespace chrono::detail

#endif
