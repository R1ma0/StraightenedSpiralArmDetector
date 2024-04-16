#include "thread_pool.hpp"

ThreadPool::ThreadPool(size_t numThreads)
{
	for (size_t i = 0; i < numThreads; ++i)
	{
		threads.emplace_back([this] {
			while (true)
			{
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock(queueMutex);
					cv.wait(lock, [this] {
						return !tasks.empty() || stop;
					});

					if (stop && tasks.empty())
					{
						return;
					}

					task = std::move(tasks.front());
					tasks.pop();
				}

				task();
			}
		});
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;
	}

	cv.notify_all();

	for (auto& thread : threads)
	{
		thread.join();
	}
}

void ThreadPool::Enqueue(std::function<void()> task)
{
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		tasks.emplace(std::move(task));
	}

	cv.notify_one();
}

void ThreadPool::ClearQueue()
{
	std::queue<std::function<void()>> empty;
	std::swap(tasks, empty);
}