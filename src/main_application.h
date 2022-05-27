#pragma once

#include "core.h"

// must be specified by client side
extern void ON_GE_INIT();

namespace ge {
	
	class Engine {
		
	public:
		
		// calls ON_GE_INIT()
		void run() const noexcept;
		
		static inline Engine& instance() noexcept {
			static Engine engine_instance;
			return engine_instance;
		}
		
		constexpr const std::thread::id& get_engine_thread_id() const noexcept {
			return this->m_engine_thread_id;
		}
		
	private:
		
		Engine(const Engine&) = delete;
		void operator = (const Engine&) = delete;
		
		inline Engine() noexcept :
		m_engine_thread_id(std::this_thread::get_id())
		{ }
		
		inline ~Engine() noexcept { }
		
		friend void m_destruct_engine(Engine& engine_instance) noexcept;
		
	private:
		
		std::thread::id m_engine_thread_id;
		
	};
	
} /// namespace ge
