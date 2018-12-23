# Chrono
C++11 Timer wrappers based on Boost.Asio timers

* Repeatable
```c++
// set by construct argument or as below
timer.Recursive(true);
```
* Cancellable
```c++
// Stopped by destruction or as below
timer.Stop();
```
* Point-based or Duration-based
* Thread-safed callback supported by asio::strand as io executor
```c++
boost::asio::strand strand;
DurationTimer timer{strand, std::chrono::second{1}};
```

# Uasge
## Point timer
* One-time timer by default

* Declaration
```c++
template <class IntervalType = std::chrono::hours,
          class IOExecutor   = boost::asio::io_context,
          class Timer        = boost::asio::system_timer,
          class TimePoint    = GetTimeType<Timer>>
class PointTimer
```

* Example
```c++
auto second_from_now =
   std::chrono::system_clock::now() + std::chrono::seconds{1};
boost::asio::io_context ioc;

PointTimer timer{ioc, second_from_now};
timer.Start([]() { std::cout << "timer expired." << std::endl; }); 

ioc.run();
```

## Duration timer
* Repeat by default

* Declaration
```c++
template <class IntervalType = std::chrono::milliseconds,
          class IOExecutor   = boost::asio::io_context,
          class Timer        = boost::asio::steady_timer>
class DurationTimer
```

* Example
```c++
auto start_time = std::chrono::steady_clock::now();
boost::asio::io_context ioc;

DurationTimer timer{ioc, std::chrono::duration<double>{1}, false};
timer.Start([]() { std::cout << "timer expired." << std::endl; });

ioc.run();
```

## Point timer with boost ptime
* Example

```c++
using namespace boost::posix_time;
auto second_from_now = second_clock::universal_time() + seconds{1};
boost::asio::io_context ioc;

PointTimer<hours, boost::asio::io_context, boost::asio::deadline_timer> timer{
    ioc, second_from_now};
timer.Start([]() { std::cout << "timer expired." << std::endl; });
ioc.run();
```

## Duration timer with thread-safed callback 

* Example
```c++
auto start_time = std::chrono::steady_clock::now();
boost::asio::strand strand;

DurationTimer timer{strand, std::chrono::second{1}, false};
timer.Start([]() { std::cout << "timer expired." << std::endl; });

ioc.run();
```
