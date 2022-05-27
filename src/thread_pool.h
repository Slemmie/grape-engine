#pragma once

#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

namespace ge {
	
	class Thread_pool {
	
	public:
		static inline Thread_pool& instance() {
			static Thread_pool thread_pool_instance(10);
			return thread_pool_instance;
		}

		Thread_pool(unsigned int threads_count);
		~Thread_pool();
		template<typename F, typename... Args>
		void push(F&& job, Args&&... args) {
			std::function <void()> f = std::bind(job, std::forward<Args>(args)...);
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				job_queue.push(f);
			}
			queue_condition.notify_one();
		}

		bool busy();
		
	private:


		void thread_loop();

		bool terminate = false;
		std::mutex queue_mutex;
		std::condition_variable queue_condition;
		std::vector <std::thread> threads;
		std::queue <std::function<void()>> job_queue;

	};

}

