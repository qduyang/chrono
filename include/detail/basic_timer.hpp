/****************************************************************************
**
**  Copyright (c) 2018 Du Yang
**
**    Author        : Du Yang <duyang.seu@gmail.com>
**    File          : basic_timer.hpp
**    Date          : 2018/12/22 00:51:00
**    Description   : Basic Timer
**
****************************************************************************/

#ifndef CHRONO_DETAIL_BASIC_TIMER_HPP
#define CHRONO_DETAIL_BASIC_TIMER_HPP

#include <chrono>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/system_timer.hpp>

#include "expiry_policy.hpp"

namespace Chrono::Detail
{
namespace Impl
{
template <class Timer>
struct GetTimeType
{
  using type = typename Timer::time_point;
};

template <>
struct GetTimeType<boost::asio::deadline_timer>
{
  using type = typename boost::asio::deadline_timer::time_type;
};
} // namespace Impl

template <class Timer>
using GetTimeType = typename Impl::GetTimeType<Timer>::type;

template <class IntervalType = std::chrono::hours,
          class IOExecutor   = boost::asio::io_context,
          class Timer        = boost::asio::system_timer,
          class TimePoint    = GetTimeType<Timer>,
          template <class, class> class ExpiryPolicy = ExpireAtPoint>
class BasicTimer : public ExpiryPolicy<IntervalType, TimePoint>
{
 public:
  using ExpiryMgr = ExpiryPolicy<IntervalType, TimePoint>;

  template <class Interval>
  BasicTimer(IOExecutor& ioe, const TimePoint& expiry_time,
             const Interval& interval, bool recursive)
    : ExpiryMgr{expiry_time, interval},
      ioe_{ioe},
      timer_{GetIOContext(ioe)},
      recursive_{recursive}
  {
  }

  BasicTimer(IOExecutor& ioe, const TimePoint& expiry_time)
    : BasicTimer{ioe, expiry_time, 1, false}
  {
  }

  template <class Interval>
  BasicTimer(IOExecutor& ioe, const TimePoint& expiry_time,
             const Interval& interval)
    : BasicTimer{ioe, expiry_time, interval, false}
  {
  }

  BasicTimer(IOExecutor& ioe, const TimePoint& expiry_time, bool recursive)
    : BasicTimer{ioe, expiry_time, 1, recursive}
  {
  }

  template <class Rep, class Period>
  BasicTimer(IOExecutor& ioe, const TimePoint& expiry_time,
             const std::chrono::duration<Rep, Period>& interval)
    : BasicTimer{ioe, expiry_time,
                 std::chrono::duration_cast<IntervalType>(interval), false}
  {
  }

  template <class Rep, class Period>
  BasicTimer(IOExecutor& ioe, const TimePoint& expiry_time,
             const std::chrono::duration<Rep, Period>& interval, bool recursive)
    : ExpiryMgr{expiry_time,
                std::chrono::duration_cast<IntervalType>(interval)},
      ioe_{ioe},
      timer_{GetIOContext(ioe)},
      recursive_{recursive}
  {
  }

  template <class F>
  inline void Start(F&& handler)
  {
    PutTimer(std::forward<F>(handler), ioe_);
  }

  inline void Recursive(bool type)
  {
    recursive_ = type;
  }

  inline void Stop()
  {
    timer_.cancel();
  }

  ~BasicTimer()
  {
    timer_.cancel();
  }

 protected:
  static inline boost::asio::io_context& GetIOContext(
      boost::asio::io_context& ioc)
  {
    return ioc;
  }

  static inline boost::asio::io_context& GetIOContext(
      boost::asio::io_context::strand& strand)
  {
    return strand.get_io_service();
  }

  template <class F>
  inline void OnTimeout(const boost::system::error_code& ec, F&& handler)
  {
    if (ec != boost::asio::error::operation_aborted)
    {
      handler();
      if (recursive_)
      {
        PutTimer(std::forward<F>(handler), ioe_);
      }
    }
  }

  template <class F>
  inline void PutTimer(F&& handler, const boost::asio::io_context&)
  {
    ExpiryMgr::SetExpireTime(timer_);
    timer_.async_wait([this, handler = std::forward<F>(handler)](
        const boost::system::error_code& ec) {
      OnTimeout(ec, std::move(handler));
    });
  }

  template <class F>
  inline void PutTimer(F&& handler, const boost::asio::io_context::strand&)
  {
    ExpiryMgr::SetExpireTime(timer_);
    timer_.async_wait(ioe_.wrap([this, handler = std::forward<F>(handler)](
        const boost::system::error_code& ec) {
      OnTimeout(ec, std::move(handler));
    }));
  }

 private:
  IOExecutor& ioe_;
  Timer timer_;
  bool recursive_;
};

} // namespace Chrono::Detail

#endif
