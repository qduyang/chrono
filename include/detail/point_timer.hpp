/****************************************************************************
**
**  Copyright (c) 2018 Du Yang
**
**    Author        : Du Yang <duyang.seu@gmail.com>
**    File          : point_timer.hpp
**    Date          : 2018/06/06 17:30:00
**    Description   : Point Timer
**
****************************************************************************/

#ifndef CHRONO_DETAIL_POINT_TIMER_HPP
#define CHRONO_DETAIL_POINT_TIMER_HPP

#include "basic_timer.hpp"

namespace Chrono::Detail
{
template <class IntervalType = std::chrono::hours,
          class IOExecutor   = boost::asio::io_context,
          class Timer        = boost::asio::system_timer,
          class TimePoint    = GetTimeType<Timer>>
class PointTimer
  : public BasicTimer<IntervalType, IOExecutor, Timer, TimePoint, ExpireAtPoint>
{
 public:
  using Base =
      BasicTimer<IntervalType, IOExecutor, Timer, TimePoint, ExpireAtPoint>;
  using Base::BasicTimer;
};

} // namespace Chrono::Detail

#endif
