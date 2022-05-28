#pragma once

namespace ge {
	
	class Thread_pool {
	
	public:
		static inline Thread_pool& instance() {
			static Thread_pool thread_pool_instance(std::thread::hardware_concurrency());
			return thread_pool_instance;
		}

		Thread_pool(size_t threads_count);
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

		bool job_queue_empty();
		
		inline size_t count_busy() const noexcept {
			return m_busy_count;
		}
		
		inline size_t size() noexcept {
			std::unique_lock <std::mutex> lock(queue_mutex);
			return threads.size();
		}
		
	private:
		
		Thread_pool(const Thread_pool&) = delete;
		void operator = (const Thread_pool&) = delete;
		
		std::atomic <size_t> m_busy_count;

		void thread_loop();

		bool terminate = false;
		std::mutex queue_mutex;
		std::condition_variable queue_condition;
		std::vector <std::thread> threads;
		std::queue <std::function<void()>> job_queue;

	};

}

