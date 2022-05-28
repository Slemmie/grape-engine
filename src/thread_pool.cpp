#include "thread_pool.h"

namespace ge {
	Thread_pool::Thread_pool(unsigned int thread_count) {
		threads.resize(thread_count);
		for(unsigned int i = 0; i < thread_count; i++)
			threads[i] = std::thread([this] () {thread_loop();});
	}
	
	Thread_pool::~Thread_pool() {
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			terminate = true;
		}
		queue_condition.notify_all();
		for(std::thread &thread : threads) thread.join();
		threads.clear();
	}

	bool Thread_pool::job_queue_empty() {
		std::unique_lock<std::mutex> lock(queue_mutex);
		return job_queue.empty();
	}

	void Thread_pool::thread_loop() {
		while(true) {
			std::function <void()> job;
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				queue_condition.wait(lock, [this] {
					return !job_queue.empty() || terminate;
				});
				if(terminate) return;
				job = job_queue.front();
				job_queue.pop();
			}
			job();
		}
	}
}

