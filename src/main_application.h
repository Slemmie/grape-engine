#pragma once

#include "core.h"

// must be specified by client side
extern void ON_GE_INIT();

namespace ge {
	
	class engine {
		
	public:
		
		// calls ON_GE_INIT()
		void run() const noexcept;
		
		static inline engine& instance() noexcept {
			static engine engine_instance;
			return engine_instance;
		}
		
		constexpr const std::thread::id& get_engine_thread_id() const noexcept {
			return this->m_engine_thread_id;
		}
		
	private:
		
		engine(const engine&) = delete;
		void operator = (const engine&) = delete;
		
		inline engine() noexcept :
		m_engine_thread_id(std::this_thread::get_id())
		{ }
		
		inline ~engine() noexcept { }
		
		friend void m_destruct_engine(engine& engine_instance) noexcept;
		
	private:
		
		std::thread::id m_engine_thread_id;
		
	};
	
} /// namespace ge
