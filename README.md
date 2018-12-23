# Chrono
C++11 Timer wrappers based on Boost.Asio timers

* Repeatable
* Cancellable
* Point-based or Duration-based

# Uasge
## Point timer
* One-time timer by default
```c++
auto second_from_now =
   std::chrono::system_clock::now() + std::chrono::seconds{1};
boost::asio::io_context ioc;

PointTimer<std::chrono::hours> timer{ioc, second_from_now};
timer.Start(
    []() { std::cout << "timer expired." << std::endl; }); 

ioc.run();
```

## Duration timer
* repeat by default

```c++
auto start_time = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point expired_time;
boost::asio::io_context ioc;

DurationTimer<std::chrono::duration<double>> timer{ioc, 1, false};
timer.Start(
    []() { std::cout << "timer expired." << std::endl; });

ioc.run();
```

## Point timer with boost ptime
```c++
using namespace boost::posix_time;
auto second_from_now = second_clock::universal_time() + seconds{1};
ptime expire_time;
boost::asio::io_context ioc;

PointTimer<hours, boost::asio::io_context, boost::asio::deadline_timer> timer{
    ioc, second_from_now};
timer.Start(
    []() { std::cout << "timer expired." << std::endl; });
ioc.run();
```
