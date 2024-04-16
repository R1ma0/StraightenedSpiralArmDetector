#ifndef MP_THREAD_POOL_H
#define MP_THREAD_POOL_H

#include <condition_variable> 
#include <functional> 
#include <mutex> 
#include <queue> 
#include <thread> 

class ThreadPool
{
private:
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasks;
	std::mutex queueMutex;
	std::condition_variable cv;
	bool stop = false;
public:
	ThreadPool(size_t = std::thread::hardware_concurrency());
	~ThreadPool();
	bool IsTasksEmpty() { return tasks.empty(); };
	void Enqueue(std::function<void()>);
	void ClearQueue();
};

#endif