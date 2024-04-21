#ifndef MP_THREAD_POOL_H
#define MP_THREAD_POOL_H

#ifdef _SSAD_THREAD_POOL_EXPORTS
#define SSAD_THREAD_POOL_API __declspec(dllexport)
#else
#define SSAD_THREAD_POOL_API __declspec(dllimport)
#endif

#include <condition_variable> 
#include <functional> 
#include <mutex> 
#include <queue> 
#include <thread> 

class SSAD_THREAD_POOL_API ThreadPool
{
private:
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasks;
	std::mutex queueMutex;
	std::condition_variable cv;
	bool stop;
public:
	ThreadPool(size_t = std::thread::hardware_concurrency());
	~ThreadPool();
	bool IsTasksEmpty();
	void Enqueue(std::function<void()>);
	void ClearQueue();
};

#endif