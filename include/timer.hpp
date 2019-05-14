/****************************************************************************
**
**  Copyright (c) 2018 Du Yang
**
**    Author        : Du Yang <duyang.seu@gmail.com>
**    File          : timer.hpp
**    Date          : 2018/06/06 17:30:00
**    Description   : Timer
**
****************************************************************************/

#ifndef CHRONO_TIMER_HPP
#define CHRONO_TIMER_HPP

#include "detail/duration_timer.hpp"
#include "detail/point_timer.hpp"

namespace chrono
{
using detail::DurationTimer;
using detail::PointTimer;
}; // namespace chrono

#endif
