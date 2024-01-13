#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
class Timer
{
public:
	bool flag = false;
	Timer();
	Timer(const Timer& timer);
	

	~Timer()
	{
		if(flag) stop();
	}

	void start(int interval, std::function<void()> task);

	void startOnce(int delay, std::function<void()> task);

	void stop();

private:
	std::atomic<bool> _expired; // timer stopped status
	std::atomic<bool> _try_to_expire; // timer is in stop process
	std::mutex _mutex;
	std::condition_variable _expired_cond;
};

#endif // !_TIMER_H_