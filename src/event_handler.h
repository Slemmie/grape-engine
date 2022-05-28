#pragma once

#include "thread_pool.h"

namespace ge {
	
	template <typename... ARGS> class Event {
		
	public:
		
		struct Dynamic {
			
		public:
			
			constexpr Dynamic(std::function <void (ARGS...)> function) noexcept :
			m_released(false),
			m_function(function)
			{ }
			
			inline void release() noexcept {
				m_released = true;
			}
			
			constexpr bool released() const noexcept {
				return m_released;
			}
			
		private:
			
			std::atomic <bool> m_released;
			
			std::function <void (ARGS...)> m_function;
			
			friend class Event;
			
		};
		
		void callback(ARGS&&... args) noexcept {
			std::unique_lock <std::mutex> lock(m_functions_mutex);
			for (const auto& f : static_functions) {
				f(args...);
			}
			for (size_t i = 0, was_deleted = 0; i < dynamic_functions.size(); i += !was_deleted) {
				if (dynamic_functions[i]->released()) {
					std::swap(dynamic_functions[i], dynamic_functions.back());
					dynamic_functions.pop_back();
					was_deleted = true;
				} else {
					Thread_pool::instance().push(dynamic_functions[i]->m_function, args...);
					was_deleted = false;
				}
			}
		}
		
		inline void push(const Dynamic* dynamic_function) noexcept {
			std::unique_lock <std::mutex> lock(m_functions_mutex);
			dynamic_functions.emplace_back(dynamic_function);
		}
		
		inline void push(const std::function <void (ARGS...)>& static_function) noexcept {
			std::unique_lock <std::mutex> lock(m_functions_mutex);
			static_functions.emplace_back(static_function);
		}
		
	private:
		
		std::vector <const Dynamic*> dynamic_functions;
		std::vector <std::function <void (ARGS...)>> static_functions;
		
		std::mutex m_functions_mutex;
		
	};
	
#define GE_DECLARE_EVENT(_event_name, ...) class _event_name : public ::ge::Event <__VA_ARGS__> { };
	
} /// namespace ge
